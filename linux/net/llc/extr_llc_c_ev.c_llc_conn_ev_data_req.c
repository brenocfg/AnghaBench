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
struct llc_conn_state_ev {scalar_t__ prim; scalar_t__ prim_type; } ;

/* Variables and functions */
 scalar_t__ LLC_DATA_PRIM ; 
 scalar_t__ LLC_PRIM_TYPE_REQ ; 
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 

int llc_conn_ev_data_req(struct sock *sk, struct sk_buff *skb)
{
	const struct llc_conn_state_ev *ev = llc_conn_ev(skb);

	return ev->prim == LLC_DATA_PRIM &&
	       ev->prim_type == LLC_PRIM_TYPE_REQ ? 0 : 1;
}