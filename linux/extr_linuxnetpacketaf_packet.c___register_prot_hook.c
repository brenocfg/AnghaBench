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
struct packet_sock {int running; int /*<<< orphan*/  prot_hook; scalar_t__ fanout; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fanout_link (struct sock*,struct packet_sock*) ; 
 int /*<<< orphan*/  dev_add_pack (int /*<<< orphan*/ *) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

__attribute__((used)) static void __register_prot_hook(struct sock *sk)
{
	struct packet_sock *po = pkt_sk(sk);

	if (!po->running) {
		if (po->fanout)
			__fanout_link(sk, po);
		else
			dev_add_pack(&po->prot_hook);

		sock_hold(sk);
		po->running = 1;
	}
}