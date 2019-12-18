#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
typedef  int bits8 ;
struct TYPE_4__ {char attalign; int attlen; scalar_t__ attbyval; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  Pointer ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  ExpandedObjectHeader ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetEOHP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOH_flatten_into (int /*<<< orphan*/ *,char*,int) ; 
 int EOH_get_flat_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEAP_HASEXTERNAL ; 
 int /*<<< orphan*/  HEAP_HASNULL ; 
 int /*<<< orphan*/  HEAP_HASVARWIDTH ; 
 int HIGHBIT ; 
 int /*<<< orphan*/  SET_VARSIZE_SHORT (char*,int) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (int /*<<< orphan*/ ) ; 
 int VARATT_CONVERTED_SHORT_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL_EXPANDED (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ ) ; 
 scalar_t__ VARLENA_ATT_IS_PACKABLE (TYPE_1__*) ; 
 int VARSIZE (int /*<<< orphan*/ ) ; 
 int VARSIZE_EXTERNAL (int /*<<< orphan*/ ) ; 
 int VARSIZE_SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ att_align_nominal (char*,char) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_att_byval (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fill_val(Form_pg_attribute att,
		 bits8 **bit,
		 int *bitmask,
		 char **dataP,
		 uint16 *infomask,
		 Datum datum,
		 bool isnull)
{
	Size		data_length;
	char	   *data = *dataP;

	/*
	 * If we're building a null bitmap, set the appropriate bit for the
	 * current column value here.
	 */
	if (bit != NULL)
	{
		if (*bitmask != HIGHBIT)
			*bitmask <<= 1;
		else
		{
			*bit += 1;
			**bit = 0x0;
			*bitmask = 1;
		}

		if (isnull)
		{
			*infomask |= HEAP_HASNULL;
			return;
		}

		**bit |= *bitmask;
	}

	/*
	 * XXX we use the att_align macros on the pointer value itself, not on an
	 * offset.  This is a bit of a hack.
	 */
	if (att->attbyval)
	{
		/* pass-by-value */
		data = (char *) att_align_nominal(data, att->attalign);
		store_att_byval(data, datum, att->attlen);
		data_length = att->attlen;
	}
	else if (att->attlen == -1)
	{
		/* varlena */
		Pointer		val = DatumGetPointer(datum);

		*infomask |= HEAP_HASVARWIDTH;
		if (VARATT_IS_EXTERNAL(val))
		{
			if (VARATT_IS_EXTERNAL_EXPANDED(val))
			{
				/*
				 * we want to flatten the expanded value so that the
				 * constructed tuple doesn't depend on it
				 */
				ExpandedObjectHeader *eoh = DatumGetEOHP(datum);

				data = (char *) att_align_nominal(data,
												  att->attalign);
				data_length = EOH_get_flat_size(eoh);
				EOH_flatten_into(eoh, data, data_length);
			}
			else
			{
				*infomask |= HEAP_HASEXTERNAL;
				/* no alignment, since it's short by definition */
				data_length = VARSIZE_EXTERNAL(val);
				memcpy(data, val, data_length);
			}
		}
		else if (VARATT_IS_SHORT(val))
		{
			/* no alignment for short varlenas */
			data_length = VARSIZE_SHORT(val);
			memcpy(data, val, data_length);
		}
		else if (VARLENA_ATT_IS_PACKABLE(att) &&
				 VARATT_CAN_MAKE_SHORT(val))
		{
			/* convert to short varlena -- no alignment */
			data_length = VARATT_CONVERTED_SHORT_SIZE(val);
			SET_VARSIZE_SHORT(data, data_length);
			memcpy(data + 1, VARDATA(val), data_length - 1);
		}
		else
		{
			/* full 4-byte header varlena */
			data = (char *) att_align_nominal(data,
											  att->attalign);
			data_length = VARSIZE(val);
			memcpy(data, val, data_length);
		}
	}
	else if (att->attlen == -2)
	{
		/* cstring ... never needs alignment */
		*infomask |= HEAP_HASVARWIDTH;
		Assert(att->attalign == 'c');
		data_length = strlen(DatumGetCString(datum)) + 1;
		memcpy(data, DatumGetPointer(datum), data_length);
	}
	else
	{
		/* fixed-length pass-by-reference */
		data = (char *) att_align_nominal(data, att->attalign);
		Assert(att->attlen > 0);
		data_length = att->attlen;
		memcpy(data, DatumGetPointer(datum), data_length);
	}

	data += data_length;
	*dataP = data;
}