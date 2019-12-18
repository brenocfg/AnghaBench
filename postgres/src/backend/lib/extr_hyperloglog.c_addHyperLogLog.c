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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct TYPE_3__ {int registerWidth; int /*<<< orphan*/ * hashesArr; } ;
typedef  TYPE_1__ hyperLogLogState ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  Max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rho (int,int) ; 

void
addHyperLogLog(hyperLogLogState *cState, uint32 hash)
{
	uint8		count;
	uint32		index;

	/* Use the first "k" (registerWidth) bits as a zero based index */
	index = hash >> (BITS_PER_BYTE * sizeof(uint32) - cState->registerWidth);

	/* Compute the rank of the remaining 32 - "k" (registerWidth) bits */
	count = rho(hash << cState->registerWidth,
				BITS_PER_BYTE * sizeof(uint32) - cState->registerWidth);

	cState->hashesArr[index] = Max(count, cState->hashesArr[index]);
}