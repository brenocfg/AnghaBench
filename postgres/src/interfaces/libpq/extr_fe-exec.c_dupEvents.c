#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int resultInitialized; struct TYPE_8__* name; int /*<<< orphan*/ * data; int /*<<< orphan*/  passThrough; int /*<<< orphan*/  proc; } ;
typedef  TYPE_1__ PGEvent ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (size_t) ; 
 TYPE_1__* strdup (TYPE_1__*) ; 
 scalar_t__ strlen (TYPE_1__*) ; 

__attribute__((used)) static PGEvent *
dupEvents(PGEvent *events, int count, size_t *memSize)
{
	PGEvent    *newEvents;
	size_t		msize;
	int			i;

	if (!events || count <= 0)
		return NULL;

	msize = count * sizeof(PGEvent);
	newEvents = (PGEvent *) malloc(msize);
	if (!newEvents)
		return NULL;

	for (i = 0; i < count; i++)
	{
		newEvents[i].proc = events[i].proc;
		newEvents[i].passThrough = events[i].passThrough;
		newEvents[i].data = NULL;
		newEvents[i].resultInitialized = false;
		newEvents[i].name = strdup(events[i].name);
		if (!newEvents[i].name)
		{
			while (--i >= 0)
				free(newEvents[i].name);
			free(newEvents);
			return NULL;
		}
		msize += strlen(events[i].name) + 1;
	}

	*memSize += msize;
	return newEvents;
}