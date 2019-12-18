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
struct TYPE_3__ {int nDeps; scalar_t__* dependencies; } ;
typedef  TYPE_1__ DumpableObject ;
typedef  scalar_t__ DumpId ;

/* Variables and functions */

void
removeObjectDependency(DumpableObject *dobj, DumpId refId)
{
	int			i;
	int			j = 0;

	for (i = 0; i < dobj->nDeps; i++)
	{
		if (dobj->dependencies[i] != refId)
			dobj->dependencies[j++] = dobj->dependencies[i];
	}
	dobj->nDeps = j;
}