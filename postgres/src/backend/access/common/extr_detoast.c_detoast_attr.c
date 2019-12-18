#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct varlena {int dummy; } ;
struct varatt_indirect {scalar_t__ pointer; } ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  SET_VARSIZE (struct varlena*,scalar_t__) ; 
 int /*<<< orphan*/  VARATT_EXTERNAL_GET_POINTER (struct varatt_indirect,struct varlena*) ; 
 scalar_t__ VARATT_IS_COMPRESSED (struct varlena*) ; 
 int /*<<< orphan*/  VARATT_IS_EXTENDED (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_INDIRECT (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_ONDISK (struct varlena*) ; 
 scalar_t__ VARATT_IS_SHORT (struct varlena*) ; 
 struct varlena* VARDATA (struct varlena*) ; 
 struct varlena* VARDATA_SHORT (struct varlena*) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARHDRSZ_SHORT ; 
 scalar_t__ VARSIZE_ANY (struct varlena*) ; 
 scalar_t__ VARSIZE_SHORT (struct varlena*) ; 
 struct varlena* detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  memcpy (struct varlena*,struct varlena*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  pfree (struct varlena*) ; 
 struct varlena* toast_decompress_datum (struct varlena*) ; 
 struct varlena* toast_fetch_datum (struct varlena*) ; 

struct varlena *
detoast_attr(struct varlena *attr)
{
	if (VARATT_IS_EXTERNAL_ONDISK(attr))
	{
		/*
		 * This is an externally stored datum --- fetch it back from there
		 */
		attr = toast_fetch_datum(attr);
		/* If it's compressed, decompress it */
		if (VARATT_IS_COMPRESSED(attr))
		{
			struct varlena *tmp = attr;

			attr = toast_decompress_datum(tmp);
			pfree(tmp);
		}
	}
	else if (VARATT_IS_EXTERNAL_INDIRECT(attr))
	{
		/*
		 * This is an indirect pointer --- dereference it
		 */
		struct varatt_indirect redirect;

		VARATT_EXTERNAL_GET_POINTER(redirect, attr);
		attr = (struct varlena *) redirect.pointer;

		/* nested indirect Datums aren't allowed */
		Assert(!VARATT_IS_EXTERNAL_INDIRECT(attr));

		/* recurse in case value is still extended in some other way */
		attr = detoast_attr(attr);

		/* if it isn't, we'd better copy it */
		if (attr == (struct varlena *) redirect.pointer)
		{
			struct varlena *result;

			result = (struct varlena *) palloc(VARSIZE_ANY(attr));
			memcpy(result, attr, VARSIZE_ANY(attr));
			attr = result;
		}
	}
	else if (VARATT_IS_EXTERNAL_EXPANDED(attr))
	{
		/*
		 * This is an expanded-object pointer --- get flat format
		 */
		attr = detoast_external_attr(attr);
		/* flatteners are not allowed to produce compressed/short output */
		Assert(!VARATT_IS_EXTENDED(attr));
	}
	else if (VARATT_IS_COMPRESSED(attr))
	{
		/*
		 * This is a compressed value inside of the main tuple
		 */
		attr = toast_decompress_datum(attr);
	}
	else if (VARATT_IS_SHORT(attr))
	{
		/*
		 * This is a short-header varlena --- convert to 4-byte header format
		 */
		Size		data_size = VARSIZE_SHORT(attr) - VARHDRSZ_SHORT;
		Size		new_size = data_size + VARHDRSZ;
		struct varlena *new_attr;

		new_attr = (struct varlena *) palloc(new_size);
		SET_VARSIZE(new_attr, new_size);
		memcpy(VARDATA(new_attr), VARDATA_SHORT(attr), data_size);
		attr = new_attr;
	}

	return attr;
}