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
struct TYPE_4__ {scalar_t__ classoid; scalar_t__ objoid; } ;
typedef  TYPE_1__ SecLabelItem ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  Archive ;

/* Variables and functions */
 int collectSecLabels (int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static int
findSecLabels(Archive *fout, Oid classoid, Oid objoid, SecLabelItem **items)
{
	/* static storage for table of security labels */
	static SecLabelItem *labels = NULL;
	static int	nlabels = -1;

	SecLabelItem *middle = NULL;
	SecLabelItem *low;
	SecLabelItem *high;
	int			nmatch;

	/* Get security labels if we didn't already */
	if (nlabels < 0)
		nlabels = collectSecLabels(fout, &labels);

	if (nlabels <= 0)			/* no labels, so no match is possible */
	{
		*items = NULL;
		return 0;
	}

	/*
	 * Do binary search to find some item matching the object.
	 */
	low = &labels[0];
	high = &labels[nlabels - 1];
	while (low <= high)
	{
		middle = low + (high - low) / 2;

		if (classoid < middle->classoid)
			high = middle - 1;
		else if (classoid > middle->classoid)
			low = middle + 1;
		else if (objoid < middle->objoid)
			high = middle - 1;
		else if (objoid > middle->objoid)
			low = middle + 1;
		else
			break;				/* found a match */
	}

	if (low > high)				/* no matches */
	{
		*items = NULL;
		return 0;
	}

	/*
	 * Now determine how many items match the object.  The search loop
	 * invariant still holds: only items between low and high inclusive could
	 * match.
	 */
	nmatch = 1;
	while (middle > low)
	{
		if (classoid != middle[-1].classoid ||
			objoid != middle[-1].objoid)
			break;
		middle--;
		nmatch++;
	}

	*items = middle;

	middle += nmatch;
	while (middle <= high)
	{
		if (classoid != middle->classoid ||
			objoid != middle->objoid)
			break;
		middle++;
		nmatch++;
	}

	return nmatch;
}