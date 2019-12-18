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
typedef  int u8 ;
typedef  int u64 ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int GENMASK_ULL (int,int) ; 
 int PACK ; 
 int QUIRK_LITTLE_ENDIAN ; 
 int QUIRK_LSW32_IS_FIRST ; 
 int QUIRK_MSB_ON_THE_RIGHT ; 
 int UNPACK ; 
 int /*<<< orphan*/  adjust_for_msb_right_quirk (int*,int*,int*,int*) ; 
 int get_le_offset (int) ; 
 int get_reverse_lsw32_offset (int,size_t) ; 

int packing(void *pbuf, u64 *uval, int startbit, int endbit, size_t pbuflen,
	    enum packing_op op, u8 quirks)
{
	/* Number of bits for storing "uval"
	 * also width of the field to access in the pbuf
	 */
	u64 value_width;
	/* Logical byte indices corresponding to the
	 * start and end of the field.
	 */
	int plogical_first_u8, plogical_last_u8, box;

	/* startbit is expected to be larger than endbit */
	if (startbit < endbit)
		/* Invalid function call */
		return -EINVAL;

	value_width = startbit - endbit + 1;
	if (value_width > 64)
		return -ERANGE;

	/* Check if "uval" fits in "value_width" bits.
	 * If value_width is 64, the check will fail, but any
	 * 64-bit uval will surely fit.
	 */
	if (op == PACK && value_width < 64 && (*uval >= (1ull << value_width)))
		/* Cannot store "uval" inside "value_width" bits.
		 * Truncating "uval" is most certainly not desirable,
		 * so simply erroring out is appropriate.
		 */
		return -ERANGE;

	/* Initialize parameter */
	if (op == UNPACK)
		*uval = 0;

	/* Iterate through an idealistic view of the pbuf as an u64 with
	 * no quirks, u8 by u8 (aligned at u8 boundaries), from high to low
	 * logical bit significance. "box" denotes the current logical u8.
	 */
	plogical_first_u8 = startbit / 8;
	plogical_last_u8  = endbit / 8;

	for (box = plogical_first_u8; box >= plogical_last_u8; box--) {
		/* Bit indices into the currently accessed 8-bit box */
		int box_start_bit, box_end_bit, box_addr;
		u8  box_mask;
		/* Corresponding bits from the unpacked u64 parameter */
		int proj_start_bit, proj_end_bit;
		u64 proj_mask;

		/* This u8 may need to be accessed in its entirety
		 * (from bit 7 to bit 0), or not, depending on the
		 * input arguments startbit and endbit.
		 */
		if (box == plogical_first_u8)
			box_start_bit = startbit % 8;
		else
			box_start_bit = 7;
		if (box == plogical_last_u8)
			box_end_bit = endbit % 8;
		else
			box_end_bit = 0;

		/* We have determined the box bit start and end.
		 * Now we calculate where this (masked) u8 box would fit
		 * in the unpacked (CPU-readable) u64 - the u8 box's
		 * projection onto the unpacked u64. Though the
		 * box is u8, the projection is u64 because it may fall
		 * anywhere within the unpacked u64.
		 */
		proj_start_bit = ((box * 8) + box_start_bit) - endbit;
		proj_end_bit   = ((box * 8) + box_end_bit) - endbit;
		proj_mask = GENMASK_ULL(proj_start_bit, proj_end_bit);
		box_mask  = GENMASK_ULL(box_start_bit, box_end_bit);

		/* Determine the offset of the u8 box inside the pbuf,
		 * adjusted for quirks. The adjusted box_addr will be used for
		 * effective addressing inside the pbuf (so it's not
		 * logical any longer).
		 */
		box_addr = pbuflen - box - 1;
		if (quirks & QUIRK_LITTLE_ENDIAN)
			box_addr = get_le_offset(box_addr);
		if (quirks & QUIRK_LSW32_IS_FIRST)
			box_addr = get_reverse_lsw32_offset(box_addr,
							    pbuflen);

		if (op == UNPACK) {
			u64 pval;

			/* Read from pbuf, write to uval */
			pval = ((u8 *)pbuf)[box_addr] & box_mask;
			if (quirks & QUIRK_MSB_ON_THE_RIGHT)
				adjust_for_msb_right_quirk(&pval,
							   &box_start_bit,
							   &box_end_bit,
							   &box_mask);

			pval >>= box_end_bit;
			pval <<= proj_end_bit;
			*uval &= ~proj_mask;
			*uval |= pval;
		} else {
			u64 pval;

			/* Write to pbuf, read from uval */
			pval = (*uval) & proj_mask;
			pval >>= proj_end_bit;
			if (quirks & QUIRK_MSB_ON_THE_RIGHT)
				adjust_for_msb_right_quirk(&pval,
							   &box_start_bit,
							   &box_end_bit,
							   &box_mask);

			pval <<= box_end_bit;
			((u8 *)pbuf)[box_addr] &= ~box_mask;
			((u8 *)pbuf)[box_addr] |= pval;
		}
	}
	return 0;
}