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
struct socket {int dummy; } ;
struct rfcomm_session {int state; int /*<<< orphan*/  list; int /*<<< orphan*/  cfc; int /*<<< orphan*/  mtu; struct socket* sock; int /*<<< orphan*/  dlcs; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,struct socket*) ; 
 int BT_LISTEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RFCOMM_CFC_DISABLED ; 
 int /*<<< orphan*/  RFCOMM_CFC_UNKNOWN ; 
 int /*<<< orphan*/  RFCOMM_DEFAULT_MTU ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ disable_cfc ; 
 int /*<<< orphan*/  kfree (struct rfcomm_session*) ; 
 struct rfcomm_session* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_session_timeout ; 
 int /*<<< orphan*/  session_list ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_session_add(struct socket *sock, int state)
{
	struct rfcomm_session *s = kzalloc(sizeof(*s), GFP_KERNEL);

	if (!s)
		return NULL;

	BT_DBG("session %p sock %p", s, sock);

	timer_setup(&s->timer, rfcomm_session_timeout, 0);

	INIT_LIST_HEAD(&s->dlcs);
	s->state = state;
	s->sock  = sock;

	s->mtu = RFCOMM_DEFAULT_MTU;
	s->cfc = disable_cfc ? RFCOMM_CFC_DISABLED : RFCOMM_CFC_UNKNOWN;

	/* Do not increment module usage count for listening sessions.
	 * Otherwise we won't be able to unload the module. */
	if (state != BT_LISTEN)
		if (!try_module_get(THIS_MODULE)) {
			kfree(s);
			return NULL;
		}

	list_add(&s->list, &session_list);

	return s;
}