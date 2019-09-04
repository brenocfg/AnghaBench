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
typedef  int u32 ;
struct via_pll_config {int divisor; int rshift; int multiplier; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 vx855_encode_pll(struct via_pll_config pll)
{
	return (pll.divisor << 16)
		| (pll.rshift << 10)
		| pll.multiplier;
}