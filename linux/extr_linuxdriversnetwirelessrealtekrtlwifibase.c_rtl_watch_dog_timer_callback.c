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
struct TYPE_3__ {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  watchdog_wq; int /*<<< orphan*/  rtl_wq; } ;
struct rtl_priv {TYPE_1__ works; } ;
struct TYPE_4__ {int /*<<< orphan*/  watchdog_timer; } ;

/* Variables and functions */
 scalar_t__ MSECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_WATCH_DOG_TIME ; 
 struct rtl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtlpriv ; 
 TYPE_2__ works ; 

void rtl_watch_dog_timer_callback(struct timer_list *t)
{
	struct rtl_priv *rtlpriv = from_timer(rtlpriv, t, works.watchdog_timer);

	queue_delayed_work(rtlpriv->works.rtl_wq,
			   &rtlpriv->works.watchdog_wq, 0);

	mod_timer(&rtlpriv->works.watchdog_timer,
		  jiffies + MSECS(RTL_WATCH_DOG_TIME));
}