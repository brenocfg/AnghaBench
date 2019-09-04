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
struct l2tp_session {int /*<<< orphan*/  (* session_close ) (struct l2tp_session*) ;int /*<<< orphan*/  dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  __l2tp_session_unhash (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_session_queue_purge (struct l2tp_session*) ; 
 int /*<<< orphan*/  stub1 (struct l2tp_session*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int l2tp_session_delete(struct l2tp_session *session)
{
	if (test_and_set_bit(0, &session->dead))
		return 0;

	__l2tp_session_unhash(session);
	l2tp_session_queue_purge(session);
	if (session->session_close != NULL)
		(*session->session_close)(session);

	l2tp_session_dec_refcount(session);

	return 0;
}