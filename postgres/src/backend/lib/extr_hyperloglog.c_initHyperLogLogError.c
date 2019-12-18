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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  hyperLogLogState ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  initHyperLogLog (int /*<<< orphan*/ *,int) ; 
 double sqrt (double) ; 

void
initHyperLogLogError(hyperLogLogState *cState, double error)
{
	uint8		bwidth = 4;

	while (bwidth < 16)
	{
		double		m = (Size) 1 << bwidth;

		if (1.04 / sqrt(m) < error)
			break;
		bwidth++;
	}

	initHyperLogLog(cState, bwidth);
}