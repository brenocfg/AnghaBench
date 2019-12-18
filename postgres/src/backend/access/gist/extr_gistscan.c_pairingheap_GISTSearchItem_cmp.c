#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pairingheap_node ;
struct TYPE_7__ {TYPE_1__* distances; } ;
struct TYPE_6__ {int numberOfOrderBys; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; scalar_t__ isnull; } ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__ GISTSearchItem ;

/* Variables and functions */
 scalar_t__ GISTSearchItemIsHeap (TYPE_3__ const) ; 
 int float8_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pairingheap_GISTSearchItem_cmp(const pairingheap_node *a, const pairingheap_node *b, void *arg)
{
	const GISTSearchItem *sa = (const GISTSearchItem *) a;
	const GISTSearchItem *sb = (const GISTSearchItem *) b;
	IndexScanDesc scan = (IndexScanDesc) arg;
	int			i;

	/* Order according to distance comparison */
	for (i = 0; i < scan->numberOfOrderBys; i++)
	{
		if (sa->distances[i].isnull)
		{
			if (!sb->distances[i].isnull)
				return -1;
		}
		else if (sb->distances[i].isnull)
		{
			return 1;
		}
		else
		{
			int			cmp = -float8_cmp_internal(sa->distances[i].value,
												   sb->distances[i].value);

			if (cmp != 0)
				return cmp;
		}
	}

	/* Heap items go before inner pages, to ensure a depth-first search */
	if (GISTSearchItemIsHeap(*sa) && !GISTSearchItemIsHeap(*sb))
		return 1;
	if (!GISTSearchItemIsHeap(*sa) && GISTSearchItemIsHeap(*sb))
		return -1;

	return 0;
}