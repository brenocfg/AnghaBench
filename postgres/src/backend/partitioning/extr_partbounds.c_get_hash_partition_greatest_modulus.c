#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ strategy; int ndatums; int /*<<< orphan*/ ** datums; } ;
typedef  TYPE_1__* PartitionBoundInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ PARTITION_STRATEGY_HASH ; 

int
get_hash_partition_greatest_modulus(PartitionBoundInfo bound)
{
	Assert(bound && bound->strategy == PARTITION_STRATEGY_HASH);
	Assert(bound->datums && bound->ndatums > 0);
	Assert(DatumGetInt32(bound->datums[bound->ndatums - 1][0]) > 0);

	return DatumGetInt32(bound->datums[bound->ndatums - 1][0]);
}