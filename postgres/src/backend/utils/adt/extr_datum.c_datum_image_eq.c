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
typedef  scalar_t__ Pointer ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 char* DatumGetCString (scalar_t__) ; 
 char* DatumGetPointer (scalar_t__) ; 
 int /*<<< orphan*/  ERROR ; 
 struct varlena* PG_DETOAST_DATUM_PACKED (scalar_t__) ; 
 char* VARDATA_ANY (struct varlena*) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  pfree (struct varlena*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ toast_raw_datum_size (scalar_t__) ; 

bool
datum_image_eq(Datum value1, Datum value2, bool typByVal, int typLen)
{
	Size		len1,
				len2;
	bool		result = true;

	if (typByVal)
	{
		result = (value1 == value2);
	}
	else if (typLen > 0)
	{
		result = (memcmp(DatumGetPointer(value1),
						 DatumGetPointer(value2),
						 typLen) == 0);
	}
	else if (typLen == -1)
	{
		len1 = toast_raw_datum_size(value1);
		len2 = toast_raw_datum_size(value2);
		/* No need to de-toast if lengths don't match. */
		if (len1 != len2)
			result = false;
		else
		{
			struct varlena *arg1val;
			struct varlena *arg2val;

			arg1val = PG_DETOAST_DATUM_PACKED(value1);
			arg2val = PG_DETOAST_DATUM_PACKED(value2);

			result = (memcmp(VARDATA_ANY(arg1val),
							 VARDATA_ANY(arg2val),
							 len1 - VARHDRSZ) == 0);

			/* Only free memory if it's a copy made here. */
			if ((Pointer) arg1val != (Pointer) value1)
				pfree(arg1val);
			if ((Pointer) arg2val != (Pointer) value2)
				pfree(arg2val);
		}
	}
	else if (typLen == -2)
	{
		char	   *s1,
				   *s2;

		/* Compare cstring datums */
		s1 = DatumGetCString(value1);
		s2 = DatumGetCString(value2);
		len1 = strlen(s1) + 1;
		len2 = strlen(s2) + 1;
		if (len1 != len2)
			return false;
		result = (memcmp(s1, s2, len1) == 0);
	}
	else
		elog(ERROR, "unexpected typLen: %d", typLen);

	return result;
}