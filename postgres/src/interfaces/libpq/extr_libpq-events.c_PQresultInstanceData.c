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
typedef  TYPE_2__ PGresult ;
typedef  scalar_t__ PGEventProc ;

/* Variables and functions */

void *
PQresultInstanceData(const PGresult *result, PGEventProc proc)
{
	int			i;

	if (!result || !proc)
		return NULL;

	for (i = 0; i < result->nEvents; i++)
		if (result->events[i].proc == proc)
			return result->events[i].data;

	return NULL;
}