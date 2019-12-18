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
typedef  scalar_t__ float4 ;
typedef  double Selectivity ;

/* Variables and functions */

__attribute__((used)) static Selectivity
mcv_population(float4 *mcv_numbers, int mcv_nvalues)
{
	Selectivity sumcommon = 0.0;
	int			i;

	for (i = 0; i < mcv_nvalues; i++)
	{
		sumcommon += mcv_numbers[i];
	}

	return sumcommon;
}