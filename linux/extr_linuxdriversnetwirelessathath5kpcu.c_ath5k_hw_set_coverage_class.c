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
struct ath5k_hw {int ah_coverage_class; } ;

/* Variables and functions */
 int ath5k_hw_get_default_sifs (struct ath5k_hw*) ; 
 int ath5k_hw_get_default_slottime (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_ack_timeout (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_cts_timeout (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_ifs_intervals (struct ath5k_hw*,int) ; 

void
ath5k_hw_set_coverage_class(struct ath5k_hw *ah, u8 coverage_class)
{
	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	int slot_time = ath5k_hw_get_default_slottime(ah) + 3 * coverage_class;
	int ack_timeout = ath5k_hw_get_default_sifs(ah) + slot_time;
	int cts_timeout = ack_timeout;

	ath5k_hw_set_ifs_intervals(ah, slot_time);
	ath5k_hw_set_ack_timeout(ah, ack_timeout);
	ath5k_hw_set_cts_timeout(ah, cts_timeout);

	ah->ah_coverage_class = coverage_class;
}