#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t dumpId; int nDeps; scalar_t__* dependencies; } ;
typedef  TYPE_1__ DumpableObject ;
typedef  scalar_t__ DumpId ;

/* Variables and functions */
 TYPE_1__* findObjectByDumpId (scalar_t__) ; 

__attribute__((used)) static int
findLoop(DumpableObject *obj,
		 DumpId startPoint,
		 bool *processed,
		 DumpId *searchFailed,
		 DumpableObject **workspace,
		 int depth)
{
	int			i;

	/*
	 * Reject if obj is already processed.  This test prevents us from finding
	 * loops that overlap previously-processed loops.
	 */
	if (processed[obj->dumpId])
		return 0;

	/*
	 * If we've already proven there is no path from this object back to the
	 * startPoint, forget it.
	 */
	if (searchFailed[obj->dumpId] == startPoint)
		return 0;

	/*
	 * Reject if obj is already present in workspace.  This test prevents us
	 * from going into infinite recursion if we are given a startPoint object
	 * that links to a cycle it's not a member of, and it guarantees that we
	 * can't overflow the allocated size of workspace[].
	 */
	for (i = 0; i < depth; i++)
	{
		if (workspace[i] == obj)
			return 0;
	}

	/*
	 * Okay, tentatively add obj to workspace
	 */
	workspace[depth++] = obj;

	/*
	 * See if we've found a loop back to the desired startPoint; if so, done
	 */
	for (i = 0; i < obj->nDeps; i++)
	{
		if (obj->dependencies[i] == startPoint)
			return depth;
	}

	/*
	 * Recurse down each outgoing branch
	 */
	for (i = 0; i < obj->nDeps; i++)
	{
		DumpableObject *nextobj = findObjectByDumpId(obj->dependencies[i]);
		int			newDepth;

		if (!nextobj)
			continue;			/* ignore dependencies on undumped objects */
		newDepth = findLoop(nextobj,
							startPoint,
							processed,
							searchFailed,
							workspace,
							depth);
		if (newDepth > 0)
			return newDepth;
	}

	/*
	 * Remember there is no path from here back to startPoint
	 */
	searchFailed[obj->dumpId] = startPoint;

	return 0;
}