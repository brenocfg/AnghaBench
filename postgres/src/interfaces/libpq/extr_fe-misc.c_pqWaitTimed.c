#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int /*<<< orphan*/  errorMessage; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int pqSocketCheck (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pqWaitTimed(int forRead, int forWrite, PGconn *conn, time_t finish_time)
{
	int			result;

	result = pqSocketCheck(conn, forRead, forWrite, finish_time);

	if (result < 0)
		return -1;				/* errorMessage is already set */

	if (result == 0)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("timeout expired\n"));
		return 1;
	}

	return 0;
}