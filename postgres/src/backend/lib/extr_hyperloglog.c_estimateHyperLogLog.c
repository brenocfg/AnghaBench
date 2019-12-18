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
struct TYPE_3__ {int nRegisters; scalar_t__* hashesArr; double alphaMM; } ;
typedef  TYPE_1__ hyperLogLogState ;

/* Variables and functions */
 double NEG_POW_2_32 ; 
 double POW_2_32 ; 
 double log (double) ; 
 double pow (double,scalar_t__) ; 

double
estimateHyperLogLog(hyperLogLogState *cState)
{
	double		result;
	double		sum = 0.0;
	int			i;

	for (i = 0; i < cState->nRegisters; i++)
	{
		sum += 1.0 / pow(2.0, cState->hashesArr[i]);
	}

	/* result set to "raw" HyperLogLog estimate (E in the HyperLogLog paper) */
	result = cState->alphaMM / sum;

	if (result <= (5.0 / 2.0) * cState->nRegisters)
	{
		/* Small range correction */
		int			zero_count = 0;

		for (i = 0; i < cState->nRegisters; i++)
		{
			if (cState->hashesArr[i] == 0)
				zero_count++;
		}

		if (zero_count != 0)
			result = cState->nRegisters * log((double) cState->nRegisters /
											  zero_count);
	}
	else if (result > (1.0 / 30.0) * POW_2_32)
	{
		/* Large range correction */
		result = NEG_POW_2_32 * log(1.0 - (result / POW_2_32));
	}

	return result;
}