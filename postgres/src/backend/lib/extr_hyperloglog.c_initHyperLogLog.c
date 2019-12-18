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
typedef  int uint8 ;
struct TYPE_3__ {int registerWidth; int nRegisters; int arrSize; double alphaMM; int /*<<< orphan*/  hashesArr; } ;
typedef  TYPE_1__ hyperLogLogState ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  palloc0 (int) ; 

void
initHyperLogLog(hyperLogLogState *cState, uint8 bwidth)
{
	double		alpha;

	if (bwidth < 4 || bwidth > 16)
		elog(ERROR, "bit width must be between 4 and 16 inclusive");

	cState->registerWidth = bwidth;
	cState->nRegisters = (Size) 1 << bwidth;
	cState->arrSize = sizeof(uint8) * cState->nRegisters + 1;

	/*
	 * Initialize hashes array to zero, not negative infinity, per discussion
	 * of the coupon collector problem in the HyperLogLog paper
	 */
	cState->hashesArr = palloc0(cState->arrSize);

	/*
	 * "alpha" is a value that for each possible number of registers (m) is
	 * used to correct a systematic multiplicative bias present in m ^ 2 Z (Z
	 * is "the indicator function" through which we finally compute E,
	 * estimated cardinality).
	 */
	switch (cState->nRegisters)
	{
		case 16:
			alpha = 0.673;
			break;
		case 32:
			alpha = 0.697;
			break;
		case 64:
			alpha = 0.709;
			break;
		default:
			alpha = 0.7213 / (1.0 + 1.079 / cState->nRegisters);
	}

	/*
	 * Precalculate alpha m ^ 2, later used to generate "raw" HyperLogLog
	 * estimate E
	 */
	cState->alphaMM = alpha * cState->nRegisters * cState->nRegisters;
}