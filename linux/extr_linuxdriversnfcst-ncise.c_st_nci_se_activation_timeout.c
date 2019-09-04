#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int se_active; int /*<<< orphan*/  req_completion; } ;
struct st_nci_info {TYPE_1__ se_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  se_active_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct st_nci_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct st_nci_info* info ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_2__ se_info ; 

__attribute__((used)) static void st_nci_se_activation_timeout(struct timer_list *t)
{
	struct st_nci_info *info = from_timer(info, t,
					      se_info.se_active_timer);

	pr_debug("\n");

	info->se_info.se_active = false;

	complete(&info->se_info.req_completion);
}