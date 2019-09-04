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
struct timer_list {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  timer_work; } ;

/* Variables and functions */
 struct fcoe_ctlr* fip ; 
 struct fcoe_ctlr* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void fcoe_ctlr_timeout(struct timer_list *t)
{
	struct fcoe_ctlr *fip = from_timer(fip, t, timer);

	schedule_work(&fip->timer_work);
}