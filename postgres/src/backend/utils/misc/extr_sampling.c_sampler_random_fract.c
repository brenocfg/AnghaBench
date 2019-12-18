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
typedef  int /*<<< orphan*/  SamplerRandomState ;

/* Variables and functions */
 double pg_erand48 (int /*<<< orphan*/ ) ; 

double
sampler_random_fract(SamplerRandomState randstate)
{
	double		res;

	/* pg_erand48 returns a value in [0.0 - 1.0), so we must reject 0 */
	do
	{
		res = pg_erand48(randstate);
	} while (res == 0.0);
	return res;
}