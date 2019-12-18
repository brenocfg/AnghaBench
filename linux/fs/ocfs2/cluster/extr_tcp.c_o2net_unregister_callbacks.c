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
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; struct o2net_sock_container* sk_user_data; } ;
struct o2net_sock_container {int /*<<< orphan*/  sc_state_change; int /*<<< orphan*/  sc_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2net_unregister_callbacks(struct sock *sk,
			           struct o2net_sock_container *sc)
{
	int ret = 0;

	write_lock_bh(&sk->sk_callback_lock);
	if (sk->sk_user_data == sc) {
		ret = 1;
		sk->sk_user_data = NULL;
		sk->sk_data_ready = sc->sc_data_ready;
		sk->sk_state_change = sc->sc_state_change;
	}
	write_unlock_bh(&sk->sk_callback_lock);

	return ret;
}