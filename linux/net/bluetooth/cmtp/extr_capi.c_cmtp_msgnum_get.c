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
struct cmtp_session {int msgnum; } ;

/* Variables and functions */
 int CMTP_INITIAL_MSGNUM ; 

__attribute__((used)) static int cmtp_msgnum_get(struct cmtp_session *session)
{
	session->msgnum++;

	if ((session->msgnum & 0xff) > 200)
		session->msgnum = CMTP_INITIAL_MSGNUM + 1;

	return session->msgnum;
}