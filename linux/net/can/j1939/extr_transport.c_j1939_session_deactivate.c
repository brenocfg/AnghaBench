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
struct j1939_session {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int j1939_session_deactivate_locked (struct j1939_session*) ; 
 int /*<<< orphan*/  j1939_session_list_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_session_list_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool j1939_session_deactivate(struct j1939_session *session)
{
	bool active;

	j1939_session_list_lock(session->priv);
	active = j1939_session_deactivate_locked(session);
	j1939_session_list_unlock(session->priv);

	return active;
}