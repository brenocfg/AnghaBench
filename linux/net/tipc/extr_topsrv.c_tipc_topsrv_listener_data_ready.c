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
struct tipc_topsrv {int /*<<< orphan*/  awork; int /*<<< orphan*/  rcv_wq; scalar_t__ listener; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; struct tipc_topsrv* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_topsrv_listener_data_ready(struct sock *sk)
{
	struct tipc_topsrv *srv;

	read_lock_bh(&sk->sk_callback_lock);
	srv = sk->sk_user_data;
	if (srv->listener)
		queue_work(srv->rcv_wq, &srv->awork);
	read_unlock_bh(&sk->sk_callback_lock);
}