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
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOH_flatten_into (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOH_get_flat_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PointerGetDatum (struct varlena*) ; 
 int /*<<< orphan*/  VARATT_EXTERNAL_GET_POINTER (struct varatt_indirect,struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_INDIRECT (struct varlena*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_ONDISK (struct varlena*) ; 
 int /*<<< orphan*/  VARSIZE_ANY (struct varlena*) ; 
 int /*<<< orphan*/  memcpy (struct varlena*,struct varlena*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 
 struct varlena* toast_fetch_datum (struct varlena*) ; 

struct varlena *
detoast_external_attr(struct varlena *attr)
{
	struct varlena *result;

	if (VARATT_IS_EXTERNAL_ONDISK(attr))
	{
		/*
		 * This is an external stored plain value
		 */
		result = toast_fetch_datum(attr);
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

		/* recurse if value is still external in some other way */
		if (VARATT_IS_EXTERNAL(attr))
			return detoast_external_attr(attr);

		/*
		 * Copy into the caller's memory context, in case caller tries to
		 * pfree the result.
		 */
		result = (struct varlena *) palloc(VARSIZE_ANY(attr));
		memcpy(result, attr, VARSIZE_ANY(attr));
	}
	else if (VARATT_IS_EXTERNAL_EXPANDED(attr))
	{
		/*
		 * This is an expanded-object pointer --- get flat format
		 */
		ExpandedObjectHeader *eoh;
		Size		resultsize;

		eoh = DatumGetEOHP(PointerGetDatum(attr));
		resultsize = EOH_get_flat_size(eoh);
		result = (struct varlena *) palloc(resultsize);
		EOH_flatten_into(eoh, (void *) result, resultsize);
	}
	else
	{
		/*
		 * This is a plain value inside of the main tuple - why am I called?
		 */
		result = attr;
	}

	return result;
}