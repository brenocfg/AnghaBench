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
struct j1939_session {int /*<<< orphan*/  sk; int /*<<< orphan*/  transmission; } ;

/* Variables and functions */
 int /*<<< orphan*/  j1939_sock_pending_del (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __j1939_session_drop(struct j1939_session *session)
{
	if (!session->transmission)
		return;

	j1939_sock_pending_del(session->sk);
}