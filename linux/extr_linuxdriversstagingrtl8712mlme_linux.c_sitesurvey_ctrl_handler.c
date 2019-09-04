#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sitesurvey_ctrl_timer; } ;
struct TYPE_7__ {TYPE_2__ sitesurveyctrl; } ;
struct _adapter {TYPE_3__ mlmepriv; } ;
struct TYPE_5__ {int /*<<< orphan*/  sitesurvey_ctrl_timer; } ;
struct TYPE_8__ {TYPE_1__ sitesurveyctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  _r8712_sitesurvey_ctrl_handler (struct _adapter*) ; 
 struct _adapter* adapter ; 
 struct _adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_4__ mlmepriv ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static void sitesurvey_ctrl_handler(struct timer_list *t)
{
	struct _adapter *adapter =
		from_timer(adapter, t,
			   mlmepriv.sitesurveyctrl.sitesurvey_ctrl_timer);

	_r8712_sitesurvey_ctrl_handler(adapter);
	mod_timer(&adapter->mlmepriv.sitesurveyctrl.sitesurvey_ctrl_timer,
		  jiffies + msecs_to_jiffies(3000));
}