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
struct sock {int /*<<< orphan*/  sk_callback_lock; scalar_t__ sk_user_data; } ;
struct kcm_sock {int tx_stopped; int /*<<< orphan*/  tx_work; } ;
struct kcm_psock {struct kcm_sock* tx_kcm; struct kcm_mux* mux; } ;
struct kcm_mux {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kcm_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void psock_write_space(struct sock *sk)
{
	struct kcm_psock *psock;
	struct kcm_mux *mux;
	struct kcm_sock *kcm;

	read_lock_bh(&sk->sk_callback_lock);

	psock = (struct kcm_psock *)sk->sk_user_data;
	if (unlikely(!psock))
		goto out;
	mux = psock->mux;

	spin_lock_bh(&mux->lock);

	/* Check if the socket is reserved so someone is waiting for sending. */
	kcm = psock->tx_kcm;
	if (kcm && !unlikely(kcm->tx_stopped))
		queue_work(kcm_wq, &kcm->tx_work);

	spin_unlock_bh(&mux->lock);
out:
	read_unlock_bh(&sk->sk_callback_lock);
}