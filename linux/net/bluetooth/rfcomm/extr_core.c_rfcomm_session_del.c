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
struct rfcomm_session {int state; int /*<<< orphan*/  sock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int) ; 
 int BT_LISTEN ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct rfcomm_session*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_session_clear_timer (struct rfcomm_session*) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_session_del(struct rfcomm_session *s)
{
	int state = s->state;

	BT_DBG("session %p state %ld", s, s->state);

	list_del(&s->list);

	rfcomm_session_clear_timer(s);
	sock_release(s->sock);
	kfree(s);

	if (state != BT_LISTEN)
		module_put(THIS_MODULE);

	return NULL;
}