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
struct batadv_priv {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 scalar_t__ BATADV_EXPECTED_SEQNO_RANGE ; 
 scalar_t__ BATADV_TQ_LOCAL_WINDOW_SIZE ; 
 int /*<<< orphan*/  batadv_bitmap_shift_left (unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,...) ; 
 int /*<<< orphan*/  batadv_set_bit (unsigned long*,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_zero (unsigned long*,scalar_t__) ; 

bool batadv_bit_get_packet(void *priv, unsigned long *seq_bits,
			   s32 seq_num_diff, int set_mark)
{
	struct batadv_priv *bat_priv = priv;

	/* sequence number is slightly older. We already got a sequence number
	 * higher than this one, so we just mark it.
	 */
	if (seq_num_diff <= 0 && seq_num_diff > -BATADV_TQ_LOCAL_WINDOW_SIZE) {
		if (set_mark)
			batadv_set_bit(seq_bits, -seq_num_diff);
		return false;
	}

	/* sequence number is slightly newer, so we shift the window and
	 * set the mark if required
	 */
	if (seq_num_diff > 0 && seq_num_diff < BATADV_TQ_LOCAL_WINDOW_SIZE) {
		batadv_bitmap_shift_left(seq_bits, seq_num_diff);

		if (set_mark)
			batadv_set_bit(seq_bits, 0);
		return true;
	}

	/* sequence number is much newer, probably missed a lot of packets */
	if (seq_num_diff >= BATADV_TQ_LOCAL_WINDOW_SIZE &&
	    seq_num_diff < BATADV_EXPECTED_SEQNO_RANGE) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "We missed a lot of packets (%i) !\n",
			   seq_num_diff - 1);
		bitmap_zero(seq_bits, BATADV_TQ_LOCAL_WINDOW_SIZE);
		if (set_mark)
			batadv_set_bit(seq_bits, 0);
		return true;
	}

	/* received a much older packet. The other host either restarted
	 * or the old packet got delayed somewhere in the network. The
	 * packet should be dropped without calling this function if the
	 * seqno window is protected.
	 *
	 * seq_num_diff <= -BATADV_TQ_LOCAL_WINDOW_SIZE
	 * or
	 * seq_num_diff >= BATADV_EXPECTED_SEQNO_RANGE
	 */
	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Other host probably restarted!\n");

	bitmap_zero(seq_bits, BATADV_TQ_LOCAL_WINDOW_SIZE);
	if (set_mark)
		batadv_set_bit(seq_bits, 0);

	return true;
}