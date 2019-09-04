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
typedef  unsigned long long u64 ;
typedef  unsigned long u32 ;
struct crndstate {scalar_t__ rho; unsigned long long last; } ;

/* Variables and functions */
 unsigned long prandom_u32 () ; 

__attribute__((used)) static u32 get_crandom(struct crndstate *state)
{
	u64 value, rho;
	unsigned long answer;

	if (!state || state->rho == 0)	/* no correlation */
		return prandom_u32();

	value = prandom_u32();
	rho = (u64)state->rho + 1;
	answer = (value * ((1ull<<32) - rho) + state->last * rho) >> 32;
	state->last = answer;
	return answer;
}