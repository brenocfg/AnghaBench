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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ expire; int /*<<< orphan*/  timer; } ;
struct llc_sock {TYPE_1__ pf_cycle_timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  llc_conn_set_p_flag (struct sock*,int) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

int llc_conn_ac_start_p_timer(struct sock *sk, struct sk_buff *skb)
{
	struct llc_sock *llc = llc_sk(sk);

	llc_conn_set_p_flag(sk, 1);
	mod_timer(&llc->pf_cycle_timer.timer,
		  jiffies + llc->pf_cycle_timer.expire);
	return 0;
}