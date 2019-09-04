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
struct TYPE_2__ {int /*<<< orphan*/  rcv_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tcp_send_ack (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

void tcp_send_ack(struct sock *sk)
{
	__tcp_send_ack(sk, tcp_sk(sk)->rcv_nxt);
}