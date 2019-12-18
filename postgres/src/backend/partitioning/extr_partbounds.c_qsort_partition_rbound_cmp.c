#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_5__ {int /*<<< orphan*/  partcollation; int /*<<< orphan*/  partsupfunc; int /*<<< orphan*/  partnatts; } ;
struct TYPE_4__ {int /*<<< orphan*/  lower; int /*<<< orphan*/  kind; int /*<<< orphan*/  datums; } ;
typedef  TYPE_1__ PartitionRangeBound ;
typedef  TYPE_2__* PartitionKey ;

/* Variables and functions */
 int /*<<< orphan*/  partition_rbound_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int32
qsort_partition_rbound_cmp(const void *a, const void *b, void *arg)
{
	PartitionRangeBound *b1 = (*(PartitionRangeBound *const *) a);
	PartitionRangeBound *b2 = (*(PartitionRangeBound *const *) b);
	PartitionKey key = (PartitionKey) arg;

	return partition_rbound_cmp(key->partnatts, key->partsupfunc,
								key->partcollation, b1->datums, b1->kind,
								b1->lower, b2);
}