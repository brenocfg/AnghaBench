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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {TYPE_1__ rej_sent_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 TYPE_2__* llc_sk (struct sock*) ; 

int llc_conn_ac_stop_rej_timer(struct sock *sk, struct sk_buff *skb)
{
	del_timer(&llc_sk(sk)->rej_sent_timer.timer);
	return 0;
}