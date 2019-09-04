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
typedef  int u32 ;
struct canid_match {int /*<<< orphan*/  match_sff; } ;

/* Variables and functions */
 int CAN_SFF_ID_BITS ; 
 int CAN_SFF_MASK ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void em_canid_sff_match_add(struct canid_match *cm, u32 can_id,
					u32 can_mask)
{
	int i;

	/*
	 * Limit can_mask and can_id to SFF range to
	 * protect against write after end of array
	 */
	can_mask &= CAN_SFF_MASK;
	can_id &= can_mask;

	/* Single frame */
	if (can_mask == CAN_SFF_MASK) {
		set_bit(can_id, cm->match_sff);
		return;
	}

	/* All frames */
	if (can_mask == 0) {
		bitmap_fill(cm->match_sff, (1 << CAN_SFF_ID_BITS));
		return;
	}

	/*
	 * Individual frame filter.
	 * Add record (set bit to 1) for each ID that
	 * conforms particular rule
	 */
	for (i = 0; i < (1 << CAN_SFF_ID_BITS); i++) {
		if ((i & can_mask) == can_id)
			set_bit(i, cm->match_sff);
	}
}