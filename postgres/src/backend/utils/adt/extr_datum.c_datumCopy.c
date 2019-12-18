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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetEOHP (int /*<<< orphan*/ ) ; 
 struct varlena* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOH_flatten_into (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 scalar_t__ EOH_get_flat_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PointerGetDatum (char*) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (struct varlena*) ; 
 scalar_t__ VARSIZE_ANY (struct varlena*) ; 
 scalar_t__ datumGetSize (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,struct varlena*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 

Datum
datumCopy(Datum value, bool typByVal, int typLen)
{
	Datum		res;

	if (typByVal)
		res = value;
	else if (typLen == -1)
	{
		/* It is a varlena datatype */
		struct varlena *vl = (struct varlena *) DatumGetPointer(value);

		if (VARATT_IS_EXTERNAL_EXPANDED(vl))
		{
			/* Flatten into the caller's memory context */
			ExpandedObjectHeader *eoh = DatumGetEOHP(value);
			Size		resultsize;
			char	   *resultptr;

			resultsize = EOH_get_flat_size(eoh);
			resultptr = (char *) palloc(resultsize);
			EOH_flatten_into(eoh, (void *) resultptr, resultsize);
			res = PointerGetDatum(resultptr);
		}
		else
		{
			/* Otherwise, just copy the varlena datum verbatim */
			Size		realSize;
			char	   *resultptr;

			realSize = (Size) VARSIZE_ANY(vl);
			resultptr = (char *) palloc(realSize);
			memcpy(resultptr, vl, realSize);
			res = PointerGetDatum(resultptr);
		}
	}
	else
	{
		/* Pass by reference, but not varlena, so not toasted */
		Size		realSize;
		char	   *resultptr;

		realSize = datumGetSize(value, typByVal, typLen);

		resultptr = (char *) palloc(realSize);
		memcpy(resultptr, DatumGetPointer(value), realSize);
		res = PointerGetDatum(resultptr);
	}
	return res;
}