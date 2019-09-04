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
struct sock {void* sk_rcvtimeo; void* sk_sndtimeo; int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;
struct iscsi_conn {int /*<<< orphan*/  orig_state_change; int /*<<< orphan*/  orig_data_ready; TYPE_1__* sock; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 void* MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  pr_debug (char*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_target_restore_sock_callbacks(struct iscsi_conn *conn)
{
	struct sock *sk;

	if (!conn->sock)
		return;

	sk = conn->sock->sk;
	pr_debug("Entering iscsi_target_restore_sock_callbacks: conn: %p\n", conn);

	write_lock_bh(&sk->sk_callback_lock);
	if (!sk->sk_user_data) {
		write_unlock_bh(&sk->sk_callback_lock);
		return;
	}
	sk->sk_user_data = NULL;
	sk->sk_data_ready = conn->orig_data_ready;
	sk->sk_state_change = conn->orig_state_change;
	write_unlock_bh(&sk->sk_callback_lock);

	sk->sk_sndtimeo = MAX_SCHEDULE_TIMEOUT;
	sk->sk_rcvtimeo = MAX_SCHEDULE_TIMEOUT;
}