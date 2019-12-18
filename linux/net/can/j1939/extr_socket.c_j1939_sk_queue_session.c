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
struct j1939_sock {int /*<<< orphan*/  sk; int /*<<< orphan*/  sk_session_queue_lock; int /*<<< orphan*/  sk_session_queue; } ;
struct j1939_session {int /*<<< orphan*/  sk_session_queue_entry; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_session_get (struct j1939_session*) ; 
 struct j1939_sock* j1939_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_sock_pending_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool j1939_sk_queue_session(struct j1939_session *session)
{
	struct j1939_sock *jsk = j1939_sk(session->sk);
	bool empty;

	spin_lock_bh(&jsk->sk_session_queue_lock);
	empty = list_empty(&jsk->sk_session_queue);
	j1939_session_get(session);
	list_add_tail(&session->sk_session_queue_entry, &jsk->sk_session_queue);
	spin_unlock_bh(&jsk->sk_session_queue_lock);
	j1939_sock_pending_add(&jsk->sk);

	return empty;
}