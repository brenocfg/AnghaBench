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
struct TYPE_6__ {int iss_NumOrderByKeys; TYPE_1__* iss_SortSupport; } ;
struct TYPE_5__ {int (* comparator ) (int /*<<< orphan*/  const,int /*<<< orphan*/  const,TYPE_1__*) ;} ;
typedef  TYPE_1__* SortSupport ;
typedef  TYPE_2__ IndexScanState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,TYPE_1__*) ; 

__attribute__((used)) static int
cmp_orderbyvals(const Datum *adist, const bool *anulls,
				const Datum *bdist, const bool *bnulls,
				IndexScanState *node)
{
	int			i;
	int			result;

	for (i = 0; i < node->iss_NumOrderByKeys; i++)
	{
		SortSupport ssup = &node->iss_SortSupport[i];

		/*
		 * Handle nulls.  We only need to support NULLS LAST ordering, because
		 * match_pathkeys_to_index() doesn't consider indexorderby
		 * implementation otherwise.
		 */
		if (anulls[i] && !bnulls[i])
			return 1;
		else if (!anulls[i] && bnulls[i])
			return -1;
		else if (anulls[i] && bnulls[i])
			return 0;

		result = ssup->comparator(adist[i], bdist[i], ssup);
		if (result != 0)
			return result;
	}

	return 0;
}