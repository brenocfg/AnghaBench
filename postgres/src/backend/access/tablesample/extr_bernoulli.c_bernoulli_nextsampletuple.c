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
struct TYPE_5__ {scalar_t__ lt; scalar_t__ seed; scalar_t__ cutoff; } ;
struct TYPE_4__ {scalar_t__ tsm_state; } ;
typedef  TYPE_1__ SampleScanState ;
typedef  scalar_t__ OffsetNumber ;
typedef  scalar_t__ BlockNumber ;
typedef  TYPE_2__ BernoulliSamplerData ;

/* Variables and functions */
 scalar_t__ DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ FirstOffsetNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 

__attribute__((used)) static OffsetNumber
bernoulli_nextsampletuple(SampleScanState *node,
						  BlockNumber blockno,
						  OffsetNumber maxoffset)
{
	BernoulliSamplerData *sampler = (BernoulliSamplerData *) node->tsm_state;
	OffsetNumber tupoffset = sampler->lt;
	uint32		hashinput[3];

	/* Advance to first/next tuple in block */
	if (tupoffset == InvalidOffsetNumber)
		tupoffset = FirstOffsetNumber;
	else
		tupoffset++;

	/*
	 * We compute the hash by applying hash_any to an array of 3 uint32's
	 * containing the block, offset, and seed.  This is efficient to set up,
	 * and with the current implementation of hash_any, it gives
	 * machine-independent results, which is a nice property for regression
	 * testing.
	 *
	 * These words in the hash input are the same throughout the block:
	 */
	hashinput[0] = blockno;
	hashinput[2] = sampler->seed;

	/*
	 * Loop over tuple offsets until finding suitable TID or reaching end of
	 * block.
	 */
	for (; tupoffset <= maxoffset; tupoffset++)
	{
		uint32		hash;

		hashinput[1] = tupoffset;

		hash = DatumGetUInt32(hash_any((const unsigned char *) hashinput,
									   (int) sizeof(hashinput)));
		if (hash < sampler->cutoff)
			break;
	}

	if (tupoffset > maxoffset)
		tupoffset = InvalidOffsetNumber;

	sampler->lt = tupoffset;

	return tupoffset;
}