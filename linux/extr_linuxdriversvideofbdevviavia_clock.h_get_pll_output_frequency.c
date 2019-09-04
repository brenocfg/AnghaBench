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
struct via_pll_config {int rshift; } ;

/* Variables and functions */
 int get_pll_internal_frequency (int,struct via_pll_config) ; 

__attribute__((used)) static inline u32 get_pll_output_frequency(u32 ref_freq,
	struct via_pll_config pll)
{
	return get_pll_internal_frequency(ref_freq, pll) >> pll.rshift;
}