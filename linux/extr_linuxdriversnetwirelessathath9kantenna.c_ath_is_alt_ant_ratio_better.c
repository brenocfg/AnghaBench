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
struct ath_ant_comb {int ant_ratio2; int low_rssi_thresh; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ath_is_alt_ant_ratio_better(struct ath_ant_comb *antcomb,
					       int alt_ratio, int maxdelta,
					       int mindelta, int main_rssi_avg,
					       int alt_rssi_avg, int pkt_count)
{
	if (pkt_count <= 50)
		return false;

	if (alt_rssi_avg > main_rssi_avg + mindelta)
		return true;

	if (alt_ratio >= antcomb->ant_ratio2 &&
	    alt_rssi_avg >= antcomb->low_rssi_thresh &&
	    (alt_rssi_avg > main_rssi_avg + maxdelta))
		return true;

	return false;
}