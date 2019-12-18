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
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void gpio_enable_dual_edge(int gpio)
{
	int v;

	if (gpio == -1)
		return;
	v = pmac_call_feature(PMAC_FTR_READ_GPIO, NULL, gpio, 0);
	v |= 0x80; /* enable dual edge */
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, gpio, v);
}