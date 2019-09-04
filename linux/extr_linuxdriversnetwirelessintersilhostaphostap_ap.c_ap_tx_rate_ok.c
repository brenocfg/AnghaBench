#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sta_info {int tx_max_rate; int tx_supp_rates; } ;
struct TYPE_3__ {int tx_rate_control; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */

__attribute__((used)) static int ap_tx_rate_ok(int rateidx, struct sta_info *sta,
			 local_info_t *local)
{
	if (rateidx > sta->tx_max_rate ||
	    !(sta->tx_supp_rates & (1 << rateidx)))
		return 0;

	if (local->tx_rate_control != 0 &&
	    !(local->tx_rate_control & (1 << rateidx)))
		return 0;

	return 1;
}