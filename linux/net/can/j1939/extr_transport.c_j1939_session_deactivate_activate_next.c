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
struct j1939_session {int dummy; } ;

/* Variables and functions */
 scalar_t__ j1939_session_deactivate (struct j1939_session*) ; 
 int /*<<< orphan*/  j1939_sk_queue_activate_next (struct j1939_session*) ; 

__attribute__((used)) static void
j1939_session_deactivate_activate_next(struct j1939_session *session)
{
	if (j1939_session_deactivate(session))
		j1939_sk_queue_activate_next(session);
}