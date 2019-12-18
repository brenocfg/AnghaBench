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
struct TYPE_5__ {int* mapTuplesToNodes; int nNodes; int /*<<< orphan*/ * nodeLabels; } ;
typedef  TYPE_1__ spgPickSplitOut ;
struct TYPE_6__ {int nTuples; } ;
typedef  TYPE_2__ spgPickSplitIn ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ palloc (int) ; 

__attribute__((used)) static bool
checkAllTheSame(spgPickSplitIn *in, spgPickSplitOut *out, bool tooBig,
				bool *includeNew)
{
	int			theNode;
	int			limit;
	int			i;

	/* For the moment, assume we can include the new leaf tuple */
	*includeNew = true;

	/* If there's only the new leaf tuple, don't select allTheSame mode */
	if (in->nTuples <= 1)
		return false;

	/* If tuple set doesn't fit on one page, ignore the new tuple in test */
	limit = tooBig ? in->nTuples - 1 : in->nTuples;

	/* Check to see if more than one node is populated */
	theNode = out->mapTuplesToNodes[0];
	for (i = 1; i < limit; i++)
	{
		if (out->mapTuplesToNodes[i] != theNode)
			return false;
	}

	/* Nope, so override the picksplit function's decisions */

	/* If the new tuple is in its own node, it can't be included in split */
	if (tooBig && out->mapTuplesToNodes[in->nTuples - 1] != theNode)
		*includeNew = false;

	out->nNodes = 8;			/* arbitrary number of child nodes */

	/* Random assignment of tuples to nodes (note we include new tuple) */
	for (i = 0; i < in->nTuples; i++)
		out->mapTuplesToNodes[i] = i % out->nNodes;

	/* The opclass may not use node labels, but if it does, duplicate 'em */
	if (out->nodeLabels)
	{
		Datum		theLabel = out->nodeLabels[theNode];

		out->nodeLabels = (Datum *) palloc(sizeof(Datum) * out->nNodes);
		for (i = 0; i < out->nNodes; i++)
			out->nodeLabels[i] = theLabel;
	}

	/* We don't touch the prefix or the leaf tuple datum assignments */

	return true;
}