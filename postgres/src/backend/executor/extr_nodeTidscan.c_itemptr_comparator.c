#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ ItemPointerGetBlockNumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ItemPointerGetOffsetNumber (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
itemptr_comparator(const void *a, const void *b)
{
	const ItemPointerData *ipa = (const ItemPointerData *) a;
	const ItemPointerData *ipb = (const ItemPointerData *) b;
	BlockNumber ba = ItemPointerGetBlockNumber(ipa);
	BlockNumber bb = ItemPointerGetBlockNumber(ipb);
	OffsetNumber oa = ItemPointerGetOffsetNumber(ipa);
	OffsetNumber ob = ItemPointerGetOffsetNumber(ipb);

	if (ba < bb)
		return -1;
	if (ba > bb)
		return 1;
	if (oa < ob)
		return -1;
	if (oa > ob)
		return 1;
	return 0;
}