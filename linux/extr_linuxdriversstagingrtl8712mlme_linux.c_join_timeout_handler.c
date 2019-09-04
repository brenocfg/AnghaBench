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
struct TYPE_2__ {int /*<<< orphan*/  assoc_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _r8712_join_timeout_handler (struct _adapter*) ; 
 struct _adapter* adapter ; 
 struct _adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mlmepriv ; 

__attribute__((used)) static void join_timeout_handler (struct timer_list *t)
{
	struct _adapter *adapter =
		from_timer(adapter, t, mlmepriv.assoc_timer);

	_r8712_join_timeout_handler(adapter);
}