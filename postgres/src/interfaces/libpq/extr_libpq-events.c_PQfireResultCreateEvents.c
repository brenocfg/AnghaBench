#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* result; int /*<<< orphan*/ * conn; } ;
struct TYPE_7__ {int nEvents; TYPE_1__* events; } ;
struct TYPE_6__ {int resultInitialized; int /*<<< orphan*/  passThrough; int /*<<< orphan*/  (* proc ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ PGresult ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_3__ PGEventResultCreate ;

/* Variables and functions */
 int /*<<< orphan*/  PGEVT_RESULTCREATE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
PQfireResultCreateEvents(PGconn *conn, PGresult *res)
{
	int			i;

	if (!res)
		return false;

	for (i = 0; i < res->nEvents; i++)
	{
		if (!res->events[i].resultInitialized)
		{
			PGEventResultCreate evt;

			evt.conn = conn;
			evt.result = res;
			if (!res->events[i].proc(PGEVT_RESULTCREATE, &evt,
									 res->events[i].passThrough))
				return false;

			res->events[i].resultInitialized = true;
		}
	}

	return true;
}