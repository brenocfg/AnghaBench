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
struct pie_vars {int /*<<< orphan*/  burst_time; scalar_t__ avg_dq_rate; int /*<<< orphan*/  dq_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQCOUNT_INVALID ; 
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  PSCHED_NS2TICKS (int) ; 

__attribute__((used)) static void pie_vars_init(struct pie_vars *vars)
{
	vars->dq_count = DQCOUNT_INVALID;
	vars->avg_dq_rate = 0;
	/* default of 100 ms in pschedtime */
	vars->burst_time = PSCHED_NS2TICKS(100 * NSEC_PER_MSEC);
}