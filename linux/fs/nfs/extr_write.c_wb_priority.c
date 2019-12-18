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
struct writeback_control {scalar_t__ sync_mode; } ;

/* Variables and functions */
 int FLUSH_COND_STABLE ; 
 scalar_t__ WB_SYNC_ALL ; 

__attribute__((used)) static int wb_priority(struct writeback_control *wbc)
{
	int ret = 0;

	if (wbc->sync_mode == WB_SYNC_ALL)
		ret = FLUSH_COND_STABLE;
	return ret;
}