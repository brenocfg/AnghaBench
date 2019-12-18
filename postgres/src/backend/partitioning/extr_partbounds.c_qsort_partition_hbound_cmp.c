#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_2__ {int /*<<< orphan*/  remainder; int /*<<< orphan*/  modulus; } ;
typedef  TYPE_1__ PartitionHashBound ;

/* Variables and functions */
 int /*<<< orphan*/  partition_hbound_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
qsort_partition_hbound_cmp(const void *a, const void *b)
{
	PartitionHashBound *h1 = (*(PartitionHashBound *const *) a);
	PartitionHashBound *h2 = (*(PartitionHashBound *const *) b);

	return partition_hbound_cmp(h1->modulus, h1->remainder,
								h2->modulus, h2->remainder);
}