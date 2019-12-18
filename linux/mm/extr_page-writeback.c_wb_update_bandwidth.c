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
struct dirty_throttle_control {int /*<<< orphan*/  member_0; } ;
struct bdi_writeback {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDTC_INIT (struct bdi_writeback*) ; 
 int /*<<< orphan*/  __wb_update_bandwidth (struct dirty_throttle_control*,int /*<<< orphan*/ *,unsigned long,int) ; 

void wb_update_bandwidth(struct bdi_writeback *wb, unsigned long start_time)
{
	struct dirty_throttle_control gdtc = { GDTC_INIT(wb) };

	__wb_update_bandwidth(&gdtc, NULL, start_time, false);
}