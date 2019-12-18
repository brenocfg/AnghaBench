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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_sk_stop_all_timers (struct sock*,int) ; 

int llc_conn_ac_stop_all_timers(struct sock *sk, struct sk_buff *skb)
{
	llc_sk_stop_all_timers(sk, false);
	return 0;
}