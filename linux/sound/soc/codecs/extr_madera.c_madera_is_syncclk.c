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
 int EINVAL ; 
#define  MADERA_CLK_ASYNCCLK_1 132 
#define  MADERA_CLK_ASYNCCLK_2 131 
#define  MADERA_CLK_SYSCLK_1 130 
#define  MADERA_CLK_SYSCLK_2 129 
#define  MADERA_CLK_SYSCLK_3 128 

__attribute__((used)) static int madera_is_syncclk(int clk_id)
{
	switch (clk_id) {
	case MADERA_CLK_SYSCLK_1:
	case MADERA_CLK_SYSCLK_2:
	case MADERA_CLK_SYSCLK_3:
		return 1;
	case MADERA_CLK_ASYNCCLK_1:
	case MADERA_CLK_ASYNCCLK_2:
		return 0;
	default:
		return -EINVAL;
	}
}