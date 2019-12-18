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
struct cmtp_session {int dummy; } ;
struct cmtp_conninfo {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __cmtp_copy_session (struct cmtp_session*,struct cmtp_conninfo*) ; 
 struct cmtp_session* __cmtp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int cmtp_get_conninfo(struct cmtp_conninfo *ci)
{
	struct cmtp_session *session;
	int err = 0;

	down_read(&cmtp_session_sem);

	session = __cmtp_get_session(&ci->bdaddr);
	if (session)
		__cmtp_copy_session(session, ci);
	else
		err = -ENOENT;

	up_read(&cmtp_session_sem);
	return err;
}