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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct fjes_hw {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 size_t readl (int /*<<< orphan*/ *) ; 

u32 fjes_hw_rd32(struct fjes_hw *hw, u32 reg)
{
	u8 *base = hw->base;
	u32 value = 0;

	value = readl(&base[reg]);

	return value;
}