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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_2__ sk_write_queue; } ;
struct TYPE_3__ {int tx_work_scheduled; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_purge (TYPE_2__*) ; 
 TYPE_1__* nfc_rawsock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rawsock_write_queue_purge(struct sock *sk)
{
	pr_debug("sk=%p\n", sk);

	spin_lock_bh(&sk->sk_write_queue.lock);
	__skb_queue_purge(&sk->sk_write_queue);
	nfc_rawsock(sk)->tx_work_scheduled = false;
	spin_unlock_bh(&sk->sk_write_queue.lock);
}