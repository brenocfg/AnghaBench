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
struct pppol2tp_session {int /*<<< orphan*/  owner; int /*<<< orphan*/  sk_lock; } ;
struct l2tp_session {int /*<<< orphan*/  show; int /*<<< orphan*/  recv_skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_L2TP_DEBUGFS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct pppol2tp_session* l2tp_session_priv (struct l2tp_session*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pppol2tp_recv ; 
 int /*<<< orphan*/  pppol2tp_show ; 

__attribute__((used)) static void pppol2tp_session_init(struct l2tp_session *session)
{
	struct pppol2tp_session *ps;

	session->recv_skb = pppol2tp_recv;
	if (IS_ENABLED(CONFIG_L2TP_DEBUGFS))
		session->show = pppol2tp_show;

	ps = l2tp_session_priv(session);
	mutex_init(&ps->sk_lock);
	ps->owner = current->pid;
}