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
 int /*<<< orphan*/  xl_cclk_b (int) ; 

void xl_shift_cclk(int count)
{
	int i;

	for (i = 0; i < count; i++) {
		xl_cclk_b(1);
		xl_cclk_b(0);
	}
}