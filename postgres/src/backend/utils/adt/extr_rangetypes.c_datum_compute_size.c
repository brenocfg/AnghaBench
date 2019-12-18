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
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_IS_PACKABLE (int /*<<< orphan*/ ,char) ; 
 scalar_t__ VARATT_CAN_MAKE_SHORT (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_CONVERTED_SHORT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_addlength_datum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  att_align_datum (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Size
datum_compute_size(Size data_length, Datum val, bool typbyval, char typalign,
				   int16 typlen, char typstorage)
{
	if (TYPE_IS_PACKABLE(typlen, typstorage) &&
		VARATT_CAN_MAKE_SHORT(DatumGetPointer(val)))
	{
		/*
		 * we're anticipating converting to a short varlena header, so adjust
		 * length and don't count any alignment
		 */
		data_length += VARATT_CONVERTED_SHORT_SIZE(DatumGetPointer(val));
	}
	else
	{
		data_length = att_align_datum(data_length, typalign, typlen, val);
		data_length = att_addlength_datum(data_length, typlen, val);
	}

	return data_length;
}