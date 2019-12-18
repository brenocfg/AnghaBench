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
struct TYPE_4__ {int dumpId; int nDeps; int* dependencies; } ;
typedef  TYPE_1__ DumpableObject ;
typedef  int DumpId ;

/* Variables and functions */
 int /*<<< orphan*/  addHeapElement (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int /*<<< orphan*/  free (int*) ; 
 int getMaxDumpId () ; 
 scalar_t__ pg_malloc (int) ; 
 scalar_t__ pg_malloc0 (int) ; 
 int removeHeapElement (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
TopoSort(DumpableObject **objs,
		 int numObjs,
		 DumpableObject **ordering, /* output argument */
		 int *nOrdering)		/* output argument */
{
	DumpId		maxDumpId = getMaxDumpId();
	int		   *pendingHeap;
	int		   *beforeConstraints;
	int		   *idMap;
	DumpableObject *obj;
	int			heapLength;
	int			i,
				j,
				k;

	/*
	 * This is basically the same algorithm shown for topological sorting in
	 * Knuth's Volume 1.  However, we would like to minimize unnecessary
	 * rearrangement of the input ordering; that is, when we have a choice of
	 * which item to output next, we always want to take the one highest in
	 * the original list.  Therefore, instead of maintaining an unordered
	 * linked list of items-ready-to-output as Knuth does, we maintain a heap
	 * of their item numbers, which we can use as a priority queue.  This
	 * turns the algorithm from O(N) to O(N log N) because each insertion or
	 * removal of a heap item takes O(log N) time.  However, that's still
	 * plenty fast enough for this application.
	 */

	*nOrdering = numObjs;		/* for success return */

	/* Eliminate the null case */
	if (numObjs <= 0)
		return true;

	/* Create workspace for the above-described heap */
	pendingHeap = (int *) pg_malloc(numObjs * sizeof(int));

	/*
	 * Scan the constraints, and for each item in the input, generate a count
	 * of the number of constraints that say it must be before something else.
	 * The count for the item with dumpId j is stored in beforeConstraints[j].
	 * We also make a map showing the input-order index of the item with
	 * dumpId j.
	 */
	beforeConstraints = (int *) pg_malloc0((maxDumpId + 1) * sizeof(int));
	idMap = (int *) pg_malloc((maxDumpId + 1) * sizeof(int));
	for (i = 0; i < numObjs; i++)
	{
		obj = objs[i];
		j = obj->dumpId;
		if (j <= 0 || j > maxDumpId)
			fatal("invalid dumpId %d", j);
		idMap[j] = i;
		for (j = 0; j < obj->nDeps; j++)
		{
			k = obj->dependencies[j];
			if (k <= 0 || k > maxDumpId)
				fatal("invalid dependency %d", k);
			beforeConstraints[k]++;
		}
	}

	/*
	 * Now initialize the heap of items-ready-to-output by filling it with the
	 * indexes of items that already have beforeConstraints[id] == 0.
	 *
	 * The essential property of a heap is heap[(j-1)/2] >= heap[j] for each j
	 * in the range 1..heapLength-1 (note we are using 0-based subscripts
	 * here, while the discussion in Knuth assumes 1-based subscripts). So, if
	 * we simply enter the indexes into pendingHeap[] in decreasing order, we
	 * a-fortiori have the heap invariant satisfied at completion of this
	 * loop, and don't need to do any sift-up comparisons.
	 */
	heapLength = 0;
	for (i = numObjs; --i >= 0;)
	{
		if (beforeConstraints[objs[i]->dumpId] == 0)
			pendingHeap[heapLength++] = i;
	}

	/*--------------------
	 * Now emit objects, working backwards in the output list.  At each step,
	 * we use the priority heap to select the last item that has no remaining
	 * before-constraints.  We remove that item from the heap, output it to
	 * ordering[], and decrease the beforeConstraints count of each of the
	 * items it was constrained against.  Whenever an item's beforeConstraints
	 * count is thereby decreased to zero, we insert it into the priority heap
	 * to show that it is a candidate to output.  We are done when the heap
	 * becomes empty; if we have output every element then we succeeded,
	 * otherwise we failed.
	 * i = number of ordering[] entries left to output
	 * j = objs[] index of item we are outputting
	 * k = temp for scanning constraint list for item j
	 *--------------------
	 */
	i = numObjs;
	while (heapLength > 0)
	{
		/* Select object to output by removing largest heap member */
		j = removeHeapElement(pendingHeap, heapLength--);
		obj = objs[j];
		/* Output candidate to ordering[] */
		ordering[--i] = obj;
		/* Update beforeConstraints counts of its predecessors */
		for (k = 0; k < obj->nDeps; k++)
		{
			int			id = obj->dependencies[k];

			if ((--beforeConstraints[id]) == 0)
				addHeapElement(idMap[id], pendingHeap, heapLength++);
		}
	}

	/*
	 * If we failed, report the objects that couldn't be output; these are the
	 * ones with beforeConstraints[] still nonzero.
	 */
	if (i != 0)
	{
		k = 0;
		for (j = 1; j <= maxDumpId; j++)
		{
			if (beforeConstraints[j] != 0)
				ordering[k++] = objs[idMap[j]];
		}
		*nOrdering = k;
	}

	/* Done */
	free(pendingHeap);
	free(beforeConstraints);
	free(idMap);

	return (i == 0);
}