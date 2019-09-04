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
struct kcm_psock {int /*<<< orphan*/  strp; } ;

/* Variables and functions */
 scalar_t__ likely (struct kcm_psock*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_data_ready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psock_data_ready(struct sock *sk)
{
	struct kcm_psock *psock;

	read_lock_bh(&sk->sk_callback_lock);

	psock = (struct kcm_psock *)sk->sk_user_data;
	if (likely(psock))
		strp_data_ready(&psock->strp);

	read_unlock_bh(&sk->sk_callback_lock);
}