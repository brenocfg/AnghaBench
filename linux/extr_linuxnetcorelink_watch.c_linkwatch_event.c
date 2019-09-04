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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __linkwatch_run_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  linkwatch_nextevent ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void linkwatch_event(struct work_struct *dummy)
{
	rtnl_lock();
	__linkwatch_run_queue(time_after(linkwatch_nextevent, jiffies));
	rtnl_unlock();
}