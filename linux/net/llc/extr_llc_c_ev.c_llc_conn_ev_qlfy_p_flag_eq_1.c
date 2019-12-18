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
struct TYPE_2__ {int p_flag; } ;

/* Variables and functions */
 TYPE_1__* llc_sk (struct sock*) ; 

int llc_conn_ev_qlfy_p_flag_eq_1(struct sock *sk, struct sk_buff *skb)
{
	return llc_sk(sk)->p_flag != 1;
}