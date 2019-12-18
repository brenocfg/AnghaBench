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
 int /*<<< orphan*/  reg_process_pending_beacon_hints () ; 
 int /*<<< orphan*/  reg_process_pending_hints () ; 
 int /*<<< orphan*/  reg_process_self_managed_hints () ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void reg_todo(struct work_struct *work)
{
	rtnl_lock();
	reg_process_pending_hints();
	reg_process_pending_beacon_hints();
	reg_process_self_managed_hints();
	rtnl_unlock();
}