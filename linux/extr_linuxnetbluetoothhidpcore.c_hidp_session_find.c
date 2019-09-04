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
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 struct hidp_session* __hidp_session_find (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_session_get (struct hidp_session*) ; 
 int /*<<< orphan*/  hidp_session_sem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hidp_session *hidp_session_find(const bdaddr_t *bdaddr)
{
	struct hidp_session *session;

	down_read(&hidp_session_sem);

	session = __hidp_session_find(bdaddr);
	if (session)
		hidp_session_get(session);

	up_read(&hidp_session_sem);

	return session;
}