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
struct llc_sock {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLC_CONN_EV_TYPE_BUSY_TMR ; 
 TYPE_1__ busy_state_timer ; 
 struct llc_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct llc_sock* llc ; 
 int /*<<< orphan*/  llc_conn_tmr_common_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void llc_conn_busy_tmr_cb(struct timer_list *t)
{
	struct llc_sock *llc = from_timer(llc, t, busy_state_timer.timer);

	llc_conn_tmr_common_cb(&llc->sk, LLC_CONN_EV_TYPE_BUSY_TMR);
}