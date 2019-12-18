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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  SamplerRandomState ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int gcd (int,int) ; 
 int sampler_random_fract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32
random_relative_prime(uint32 n, SamplerRandomState randstate)
{
	uint32		r;

	/* Safety check to avoid infinite loop or zero result for small n. */
	if (n <= 1)
		return 1;

	/*
	 * This should only take 2 or 3 iterations as the probability of 2 numbers
	 * being relatively prime is ~61%; but just in case, we'll include a
	 * CHECK_FOR_INTERRUPTS in the loop.
	 */
	do
	{
		CHECK_FOR_INTERRUPTS();
		r = (uint32) (sampler_random_fract(randstate) * n);
	} while (r == 0 || gcd(r, n) > 1);

	return r;
}