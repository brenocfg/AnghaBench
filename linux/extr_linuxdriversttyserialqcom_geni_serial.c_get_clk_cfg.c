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

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 unsigned long* root_freq ; 

__attribute__((used)) static unsigned long get_clk_cfg(unsigned long clk_freq)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(root_freq); i++) {
		if (!(root_freq[i] % clk_freq))
			return root_freq[i];
	}
	return 0;
}