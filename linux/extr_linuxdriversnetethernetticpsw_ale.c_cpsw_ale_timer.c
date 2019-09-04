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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct cpsw_ale {TYPE_1__ timer; scalar_t__ ageout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_AGEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct cpsw_ale* ale ; 
 int /*<<< orphan*/  cpsw_ale_control_set (struct cpsw_ale*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cpsw_ale* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void cpsw_ale_timer(struct timer_list *t)
{
	struct cpsw_ale *ale = from_timer(ale, t, timer);

	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);

	if (ale->ageout) {
		ale->timer.expires = jiffies + ale->ageout;
		add_timer(&ale->timer);
	}
}