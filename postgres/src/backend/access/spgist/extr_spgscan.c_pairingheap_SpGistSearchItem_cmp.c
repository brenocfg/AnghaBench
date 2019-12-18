#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pairingheap_node ;
struct TYPE_4__ {int numberOfNonNullOrderBys; } ;
struct TYPE_3__ {scalar_t__* distances; scalar_t__ isLeaf; scalar_t__ isNull; } ;
typedef  TYPE_1__ SpGistSearchItem ;
typedef  TYPE_2__* SpGistScanOpaque ;

/* Variables and functions */
 scalar_t__ isnan (scalar_t__) ; 

__attribute__((used)) static int
pairingheap_SpGistSearchItem_cmp(const pairingheap_node *a,
								 const pairingheap_node *b, void *arg)
{
	const SpGistSearchItem *sa = (const SpGistSearchItem *) a;
	const SpGistSearchItem *sb = (const SpGistSearchItem *) b;
	SpGistScanOpaque so = (SpGistScanOpaque) arg;
	int			i;

	if (sa->isNull)
	{
		if (!sb->isNull)
			return -1;
	}
	else if (sb->isNull)
	{
		return 1;
	}
	else
	{
		/* Order according to distance comparison */
		for (i = 0; i < so->numberOfNonNullOrderBys; i++)
		{
			if (isnan(sa->distances[i]) && isnan(sb->distances[i]))
				continue;		/* NaN == NaN */
			if (isnan(sa->distances[i]))
				return -1;		/* NaN > number */
			if (isnan(sb->distances[i]))
				return 1;		/* number < NaN */
			if (sa->distances[i] != sb->distances[i])
				return (sa->distances[i] < sb->distances[i]) ? 1 : -1;
		}
	}

	/* Leaf items go before inner pages, to ensure a depth-first search */
	if (sa->isLeaf && !sb->isLeaf)
		return 1;
	if (!sa->isLeaf && sb->isLeaf)
		return -1;

	return 0;
}