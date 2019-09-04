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
struct wb_domain {int /*<<< orphan*/  completions; int /*<<< orphan*/  dirty_limit_tstamp; int /*<<< orphan*/  period_timer; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_DEFERRABLE ; 
 int fprop_global_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct wb_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_period ; 

int wb_domain_init(struct wb_domain *dom, gfp_t gfp)
{
	memset(dom, 0, sizeof(*dom));

	spin_lock_init(&dom->lock);

	timer_setup(&dom->period_timer, writeout_period, TIMER_DEFERRABLE);

	dom->dirty_limit_tstamp = jiffies;

	return fprop_global_init(&dom->completions, gfp);
}