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
struct rfcomm_session {int /*<<< orphan*/  dlcs; } ;
struct rfcomm_dlc {struct rfcomm_session* session; int /*<<< orphan*/  list; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,struct rfcomm_session*) ; 
 int /*<<< orphan*/  RFCOMM_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_dlc_put (struct rfcomm_dlc*) ; 
 int /*<<< orphan*/  rfcomm_session_set_timer (struct rfcomm_session*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_dlc_unlink(struct rfcomm_dlc *d)
{
	struct rfcomm_session *s = d->session;

	BT_DBG("dlc %p refcnt %d session %p", d, refcount_read(&d->refcnt), s);

	list_del(&d->list);
	d->session = NULL;
	rfcomm_dlc_put(d);

	if (list_empty(&s->dlcs))
		rfcomm_session_set_timer(s, RFCOMM_IDLE_TIMEOUT);
}