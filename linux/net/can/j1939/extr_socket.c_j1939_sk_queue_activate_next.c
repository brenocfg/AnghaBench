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
struct j1939_sock {int /*<<< orphan*/  sk_session_queue_lock; } ;
struct j1939_session {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 struct j1939_sock* j1939_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_sk_queue_activate_next_locked (struct j1939_session*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void j1939_sk_queue_activate_next(struct j1939_session *session)
{
	struct j1939_sock *jsk;

	if (!session->sk)
		return;

	jsk = j1939_sk(session->sk);

	spin_lock_bh(&jsk->sk_session_queue_lock);
	j1939_sk_queue_activate_next_locked(session);
	spin_unlock_bh(&jsk->sk_session_queue_lock);
}