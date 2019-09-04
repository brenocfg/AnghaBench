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
#define  ARIZONA_CLK_ASYNCCLK 129 
#define  ARIZONA_CLK_SYSCLK 128 

__attribute__((used)) static const char *arizona_dai_clk_str(int clk_id)
{
	switch (clk_id) {
	case ARIZONA_CLK_SYSCLK:
		return "SYSCLK";
	case ARIZONA_CLK_ASYNCCLK:
		return "ASYNCCLK";
	default:
		return "Unknown clock";
	}
}