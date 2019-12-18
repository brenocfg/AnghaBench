#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  db; int /*<<< orphan*/  queryFout; } ;
struct TYPE_5__ {char* extra; char* relname; int be_pid; } ;
typedef  TYPE_1__ PGnotify ;

/* Variables and functions */
 int /*<<< orphan*/  PQconsumeInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreemem (TYPE_1__*) ; 
 TYPE_1__* PQnotifies (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 TYPE_2__ pset ; 

__attribute__((used)) static void
PrintNotifications(void)
{
	PGnotify   *notify;

	PQconsumeInput(pset.db);
	while ((notify = PQnotifies(pset.db)) != NULL)
	{
		/* for backward compatibility, only show payload if nonempty */
		if (notify->extra[0])
			fprintf(pset.queryFout, _("Asynchronous notification \"%s\" with payload \"%s\" received from server process with PID %d.\n"),
					notify->relname, notify->extra, notify->be_pid);
		else
			fprintf(pset.queryFout, _("Asynchronous notification \"%s\" received from server process with PID %d.\n"),
					notify->relname, notify->be_pid);
		fflush(pset.queryFout);
		PQfreemem(notify);
		PQconsumeInput(pset.db);
	}
}