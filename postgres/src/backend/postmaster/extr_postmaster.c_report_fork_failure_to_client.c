#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pg_set_noblock (int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
report_fork_failure_to_client(Port *port, int errnum)
{
	char		buffer[1000];
	int			rc;

	/* Format the error message packet (always V2 protocol) */
	snprintf(buffer, sizeof(buffer), "E%s%s\n",
			 _("could not fork new process for connection: "),
			 strerror(errnum));

	/* Set port to non-blocking.  Don't do send() if this fails */
	if (!pg_set_noblock(port->sock))
		return;

	/* We'll retry after EINTR, but ignore all other failures */
	do
	{
		rc = send(port->sock, buffer, strlen(buffer) + 1, 0);
	} while (rc < 0 && errno == EINTR);
}