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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  hashinput ;
struct TYPE_5__ {scalar_t__ tsm_state; } ;
struct TYPE_4__ {scalar_t__ nextblock; scalar_t__ seed; scalar_t__ cutoff; } ;
typedef  TYPE_1__ SystemSamplerData ;
typedef  TYPE_2__ SampleScanState ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 

__attribute__((used)) static BlockNumber
system_nextsampleblock(SampleScanState *node, BlockNumber nblocks)
{
	SystemSamplerData *sampler = (SystemSamplerData *) node->tsm_state;
	BlockNumber nextblock = sampler->nextblock;
	uint32		hashinput[2];

	/*
	 * We compute the hash by applying hash_any to an array of 2 uint32's
	 * containing the block number and seed.  This is efficient to set up, and
	 * with the current implementation of hash_any, it gives
	 * machine-independent results, which is a nice property for regression
	 * testing.
	 *
	 * These words in the hash input are the same throughout the block:
	 */
	hashinput[1] = sampler->seed;

	/*
	 * Loop over block numbers until finding suitable block or reaching end of
	 * relation.
	 */
	for (; nextblock < nblocks; nextblock++)
	{
		uint32		hash;

		hashinput[0] = nextblock;

		hash = DatumGetUInt32(hash_any((const unsigned char *) hashinput,
									   (int) sizeof(hashinput)));
		if (hash < sampler->cutoff)
			break;
	}

	if (nextblock < nblocks)
	{
		/* Found a suitable block; remember where we should start next time */
		sampler->nextblock = nextblock + 1;
		return nextblock;
	}

	/* Done, but let's reset nextblock to 0 for safety. */
	sampler->nextblock = 0;
	return InvalidBlockNumber;
}