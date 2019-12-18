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
struct packet_sock {int /*<<< orphan*/  bind_lock; int /*<<< orphan*/  prot_hook; scalar_t__ fanout; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_remove_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __fanout_unlink (struct sock*,struct packet_sock*) ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

__attribute__((used)) static void __unregister_prot_hook(struct sock *sk, bool sync)
{
	struct packet_sock *po = pkt_sk(sk);

	lockdep_assert_held_once(&po->bind_lock);

	po->running = 0;

	if (po->fanout)
		__fanout_unlink(sk, po);
	else
		__dev_remove_pack(&po->prot_hook);

	__sock_put(sk);

	if (sync) {
		spin_unlock(&po->bind_lock);
		synchronize_net();
		spin_lock(&po->bind_lock);
	}
}