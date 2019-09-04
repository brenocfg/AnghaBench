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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  BATADV_EXPECTED_SEQNO_RANGE ; 
 int /*<<< orphan*/  BATADV_RESET_PROTECTION_MS ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*) ; 
 int /*<<< orphan*/  batadv_has_timed_out (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 

bool batadv_window_protected(struct batadv_priv *bat_priv, s32 seq_num_diff,
			     s32 seq_old_max_diff, unsigned long *last_reset,
			     bool *protection_started)
{
	if (seq_num_diff <= -seq_old_max_diff ||
	    seq_num_diff >= BATADV_EXPECTED_SEQNO_RANGE) {
		if (!batadv_has_timed_out(*last_reset,
					  BATADV_RESET_PROTECTION_MS))
			return true;

		*last_reset = jiffies;
		if (protection_started)
			*protection_started = true;
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "old packet received, start protection\n");
	}

	return false;
}