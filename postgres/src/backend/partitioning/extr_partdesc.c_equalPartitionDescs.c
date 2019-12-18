#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nparts; scalar_t__* oids; int /*<<< orphan*/ * boundinfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  parttypbyval; int /*<<< orphan*/  parttyplen; int /*<<< orphan*/  partnatts; } ;
typedef  TYPE_1__* PartitionKey ;
typedef  TYPE_2__* PartitionDesc ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  partition_bounds_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
equalPartitionDescs(PartitionKey key, PartitionDesc partdesc1,
					PartitionDesc partdesc2)
{
	int			i;

	if (partdesc1 != NULL)
	{
		if (partdesc2 == NULL)
			return false;
		if (partdesc1->nparts != partdesc2->nparts)
			return false;

		Assert(key != NULL || partdesc1->nparts == 0);

		/*
		 * Same oids? If the partitioning structure did not change, that is,
		 * no partitions were added or removed to the relation, the oids array
		 * should still match element-by-element.
		 */
		for (i = 0; i < partdesc1->nparts; i++)
		{
			if (partdesc1->oids[i] != partdesc2->oids[i])
				return false;
		}

		/*
		 * Now compare partition bound collections.  The logic to iterate over
		 * the collections is private to partition.c.
		 */
		if (partdesc1->boundinfo != NULL)
		{
			if (partdesc2->boundinfo == NULL)
				return false;

			if (!partition_bounds_equal(key->partnatts, key->parttyplen,
										key->parttypbyval,
										partdesc1->boundinfo,
										partdesc2->boundinfo))
				return false;
		}
		else if (partdesc2->boundinfo != NULL)
			return false;
	}
	else if (partdesc2 != NULL)
		return false;

	return true;
}