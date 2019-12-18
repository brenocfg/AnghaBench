#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nEvents; TYPE_1__* events; } ;
struct TYPE_4__ {scalar_t__ proc; void* data; } ;
typedef  TYPE_2__ PGconn ;
typedef  scalar_t__ PGEventProc ;

/* Variables and functions */

int
PQsetInstanceData(PGconn *conn, PGEventProc proc, void *data)
{
	int			i;

	if (!conn || !proc)
		return false;

	for (i = 0; i < conn->nEvents; i++)
	{
		if (conn->events[i].proc == proc)
		{
			conn->events[i].data = data;
			return true;
		}
	}

	return false;
}