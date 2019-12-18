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
typedef  int int16 ;
typedef  int Size ;
typedef  char* Pointer ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 char* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE_SHORT (char*,int) ; 
 scalar_t__ TYPE_IS_PACKABLE (int,char) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (char*) ; 
 int VARATT_CONVERTED_SHORT_SIZE (char*) ; 
 scalar_t__ VARATT_IS_EXTERNAL (char*) ; 
 scalar_t__ VARATT_IS_SHORT (char*) ; 
 char* VARDATA (char*) ; 
 int VARSIZE (char*) ; 
 int VARSIZE_SHORT (char*) ; 
 scalar_t__ att_align_nominal (char*,char) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  store_att_byval (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Pointer
datum_write(Pointer ptr, Datum datum, bool typbyval, char typalign,
			int16 typlen, char typstorage)
{
	Size		data_length;

	if (typbyval)
	{
		/* pass-by-value */
		ptr = (char *) att_align_nominal(ptr, typalign);
		store_att_byval(ptr, datum, typlen);
		data_length = typlen;
	}
	else if (typlen == -1)
	{
		/* varlena */
		Pointer		val = DatumGetPointer(datum);

		if (VARATT_IS_EXTERNAL(val))
		{
			/*
			 * Throw error, because we must never put a toast pointer inside a
			 * range object.  Caller should have detoasted it.
			 */
			elog(ERROR, "cannot store a toast pointer inside a range");
			data_length = 0;	/* keep compiler quiet */
		}
		else if (VARATT_IS_SHORT(val))
		{
			/* no alignment for short varlenas */
			data_length = VARSIZE_SHORT(val);
			memcpy(ptr, val, data_length);
		}
		else if (TYPE_IS_PACKABLE(typlen, typstorage) &&
				 VARATT_CAN_MAKE_SHORT(val))
		{
			/* convert to short varlena -- no alignment */
			data_length = VARATT_CONVERTED_SHORT_SIZE(val);
			SET_VARSIZE_SHORT(ptr, data_length);
			memcpy(ptr + 1, VARDATA(val), data_length - 1);
		}
		else
		{
			/* full 4-byte header varlena */
			ptr = (char *) att_align_nominal(ptr, typalign);
			data_length = VARSIZE(val);
			memcpy(ptr, val, data_length);
		}
	}
	else if (typlen == -2)
	{
		/* cstring ... never needs alignment */
		Assert(typalign == 'c');
		data_length = strlen(DatumGetCString(datum)) + 1;
		memcpy(ptr, DatumGetPointer(datum), data_length);
	}
	else
	{
		/* fixed-length pass-by-reference */
		ptr = (char *) att_align_nominal(ptr, typalign);
		Assert(typlen > 0);
		data_length = typlen;
		memcpy(ptr, DatumGetPointer(datum), data_length);
	}

	ptr += data_length;

	return ptr;
}