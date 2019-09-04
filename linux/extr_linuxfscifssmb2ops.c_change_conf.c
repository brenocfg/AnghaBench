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
struct TCP_Server_Info {int credits; int echo_credits; int oplock_credits; int echoes; int oplocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_oplocks ; 

__attribute__((used)) static int
change_conf(struct TCP_Server_Info *server)
{
	server->credits += server->echo_credits + server->oplock_credits;
	server->oplock_credits = server->echo_credits = 0;
	switch (server->credits) {
	case 0:
		return 0;
	case 1:
		server->echoes = false;
		server->oplocks = false;
		break;
	case 2:
		server->echoes = true;
		server->oplocks = false;
		server->echo_credits = 1;
		break;
	default:
		server->echoes = true;
		if (enable_oplocks) {
			server->oplocks = true;
			server->oplock_credits = 1;
		} else
			server->oplocks = false;

		server->echo_credits = 1;
	}
	server->credits -= server->echo_credits + server->oplock_credits;
	return server->credits + server->echo_credits + server->oplock_credits;
}