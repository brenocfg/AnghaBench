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
typedef  enum mclk { ____Placeholder_mclk } mclk ;

/* Variables and functions */
#define  MCLK_SYSCLK 129 
#define  MCLK_ULPCLK 128 

__attribute__((used)) static inline const char *get_mclk_str(enum mclk mclk_sel)
{
	switch (mclk_sel) {
	case MCLK_SYSCLK:
		return "SYSCLK";
	case MCLK_ULPCLK:
		return "ULPCLK";
	default:
		return "Unknown";
	}
}