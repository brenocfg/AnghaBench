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

/* Variables and functions */
 int /*<<< orphan*/  tcp_rearm_rto (struct sock*) ; 
 int /*<<< orphan*/  tcp_schedule_loss_probe (struct sock*,int) ; 

__attribute__((used)) static void tcp_set_xmit_timer(struct sock *sk)
{
	if (!tcp_schedule_loss_probe(sk, true))
		tcp_rearm_rto(sk);
}