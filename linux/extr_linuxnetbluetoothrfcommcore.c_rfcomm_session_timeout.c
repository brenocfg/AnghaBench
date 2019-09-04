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
struct timer_list {int dummy; } ;
struct rfcomm_session {int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFCOMM_TIMED_OUT ; 
 struct rfcomm_session* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 struct rfcomm_session* s ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void rfcomm_session_timeout(struct timer_list *t)
{
	struct rfcomm_session *s = from_timer(s, t, timer);

	BT_DBG("session %p state %ld", s, s->state);

	set_bit(RFCOMM_TIMED_OUT, &s->flags);
	rfcomm_schedule();
}