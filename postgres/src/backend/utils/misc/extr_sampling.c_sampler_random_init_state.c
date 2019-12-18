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
typedef  int* SamplerRandomState ;

/* Variables and functions */

void
sampler_random_init_state(long seed, SamplerRandomState randstate)
{
	randstate[0] = 0x330e;		/* same as pg_erand48, but could be anything */
	randstate[1] = (unsigned short) seed;
	randstate[2] = (unsigned short) (seed >> 16);
}