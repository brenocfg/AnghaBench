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
struct hidp_session {int dummy; } ;
struct hidp_conninfo {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  hidp_copy_session (struct hidp_session*,struct hidp_conninfo*) ; 
 struct hidp_session* hidp_session_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_session_put (struct hidp_session*) ; 

int hidp_get_conninfo(struct hidp_conninfo *ci)
{
	struct hidp_session *session;

	session = hidp_session_find(&ci->bdaddr);
	if (session) {
		hidp_copy_session(session, ci);
		hidp_session_put(session);
	}

	return session ? 0 : -ENOENT;
}