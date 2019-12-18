#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* freeList; } ;
struct TYPE_6__ {TYPE_4__* hctl; } ;
struct TYPE_5__ {long nentries; } ;
typedef  TYPE_2__ HTAB ;

/* Variables and functions */
 scalar_t__ IS_PARTITIONED (TYPE_4__*) ; 
 int NUM_FREELISTS ; 

long
hash_get_num_entries(HTAB *hashp)
{
	int			i;
	long		sum = hashp->hctl->freeList[0].nentries;

	/*
	 * We currently don't bother with acquiring the mutexes; it's only
	 * sensible to call this function if you've got lock on all partitions of
	 * the table.
	 */
	if (IS_PARTITIONED(hashp->hctl))
	{
		for (i = 1; i < NUM_FREELISTS; i++)
			sum += hashp->hctl->freeList[i].nentries;
	}

	return sum;
}