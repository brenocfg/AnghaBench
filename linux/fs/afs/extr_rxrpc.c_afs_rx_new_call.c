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
struct rxrpc_call {int dummy; } ;
struct afs_net {int /*<<< orphan*/  charge_preallocation_work; } ;

/* Variables and functions */
 struct afs_net* afs_sock2net (struct sock*) ; 
 int /*<<< orphan*/  afs_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_rx_new_call(struct sock *sk, struct rxrpc_call *rxcall,
			    unsigned long user_call_ID)
{
	struct afs_net *net = afs_sock2net(sk);

	queue_work(afs_wq, &net->charge_preallocation_work);
}