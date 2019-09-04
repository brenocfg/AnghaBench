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
struct dql {int /*<<< orphan*/  slack_start_time; int /*<<< orphan*/  lowest_slack; scalar_t__ prev_ovlimit; scalar_t__ prev_last_obj_cnt; scalar_t__ prev_num_queued; scalar_t__ last_obj_cnt; scalar_t__ num_completed; scalar_t__ num_queued; scalar_t__ limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  jiffies ; 

void dql_reset(struct dql *dql)
{
	/* Reset all dynamic values */
	dql->limit = 0;
	dql->num_queued = 0;
	dql->num_completed = 0;
	dql->last_obj_cnt = 0;
	dql->prev_num_queued = 0;
	dql->prev_last_obj_cnt = 0;
	dql->prev_ovlimit = 0;
	dql->lowest_slack = UINT_MAX;
	dql->slack_start_time = jiffies;
}