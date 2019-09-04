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
struct _adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rpwm_check_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rpwm_check_handler (struct _adapter*) ; 
 struct _adapter* adapter ; 
 struct _adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ pwrctrlpriv ; 

__attribute__((used)) static void rpwm_check_handler (struct timer_list *t)
{
	struct _adapter *adapter =
		from_timer(adapter, t, pwrctrlpriv.rpwm_check_timer);

	_rpwm_check_handler(adapter);
}