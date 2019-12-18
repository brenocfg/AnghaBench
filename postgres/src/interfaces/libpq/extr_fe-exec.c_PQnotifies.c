#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * notifyTail; TYPE_1__* notifyHead; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ PGnotify ;
typedef  TYPE_2__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  parseInput (TYPE_2__*) ; 

PGnotify *
PQnotifies(PGconn *conn)
{
	PGnotify   *event;

	if (!conn)
		return NULL;

	/* Parse any available data to see if we can extract NOTIFY messages. */
	parseInput(conn);

	event = conn->notifyHead;
	if (event)
	{
		conn->notifyHead = event->next;
		if (!conn->notifyHead)
			conn->notifyTail = NULL;
		event->next = NULL;		/* don't let app see the internal state */
	}
	return event;
}