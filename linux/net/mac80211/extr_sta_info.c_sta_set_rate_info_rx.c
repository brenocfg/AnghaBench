#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sta_info {int /*<<< orphan*/  local; } ;
struct rate_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_rate; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ STA_STATS_RATE_INVALID ; 
 TYPE_1__* sta_get_last_rx_stats (struct sta_info*) ; 
 int /*<<< orphan*/  sta_stats_decode_rate (int /*<<< orphan*/ ,scalar_t__,struct rate_info*) ; 

__attribute__((used)) static int sta_set_rate_info_rx(struct sta_info *sta, struct rate_info *rinfo)
{
	u16 rate = READ_ONCE(sta_get_last_rx_stats(sta)->last_rate);

	if (rate == STA_STATS_RATE_INVALID)
		return -EINVAL;

	sta_stats_decode_rate(sta->local, rate, rinfo);
	return 0;
}