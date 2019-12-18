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
struct packet_sock {scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister_prot_hook (struct sock*,int) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 

__attribute__((used)) static void unregister_prot_hook(struct sock *sk, bool sync)
{
	struct packet_sock *po = pkt_sk(sk);

	if (po->running)
		__unregister_prot_hook(sk, sync);
}