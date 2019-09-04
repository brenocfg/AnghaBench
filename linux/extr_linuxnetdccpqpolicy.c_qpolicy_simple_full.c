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
struct TYPE_3__ {scalar_t__ qlen; } ;
struct sock {TYPE_1__ sk_write_queue; } ;
struct TYPE_4__ {scalar_t__ dccps_tx_qlen; } ;

/* Variables and functions */
 TYPE_2__* dccp_sk (struct sock*) ; 

__attribute__((used)) static bool qpolicy_simple_full(struct sock *sk)
{
	return dccp_sk(sk)->dccps_tx_qlen &&
	       sk->sk_write_queue.qlen >= dccp_sk(sk)->dccps_tx_qlen;
}