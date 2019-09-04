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
typedef  scalar_t__ u16 ;
struct carl9170_sta_tid {int bsn; scalar_t__ snx; int /*<<< orphan*/  bitmap; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 scalar_t__ CARL9170_BAW_BITS ; 
 scalar_t__ SEQ_DIFF (scalar_t__,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_shift_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  test_and_clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_tx_shift_bm(struct ar9170 *ar,
	struct carl9170_sta_tid *tid_info, u16 seq)
{
	u16 off;

	off = SEQ_DIFF(seq, tid_info->bsn);

	if (WARN_ON_ONCE(off >= CARL9170_BAW_BITS))
		return;

	/*
	 * Sanity check. For each MPDU we set the bit in bitmap and
	 * clear it once we received the tx_status.
	 * But if the bit is already cleared then we've been bitten
	 * by a bug.
	 */
	WARN_ON_ONCE(!test_and_clear_bit(off, tid_info->bitmap));

	off = SEQ_DIFF(tid_info->snx, tid_info->bsn);
	if (WARN_ON_ONCE(off >= CARL9170_BAW_BITS))
		return;

	if (!bitmap_empty(tid_info->bitmap, off))
		off = find_first_bit(tid_info->bitmap, off);

	tid_info->bsn += off;
	tid_info->bsn &= 0x0fff;

	bitmap_shift_right(tid_info->bitmap, tid_info->bitmap,
			   off, CARL9170_BAW_BITS);
}