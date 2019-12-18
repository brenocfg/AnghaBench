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
struct ep93xx_ac97_info {unsigned int regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (unsigned int,unsigned int) ; 

__attribute__((used)) static inline void ep93xx_ac97_write_reg(struct ep93xx_ac97_info *info,
					 unsigned reg, unsigned val)
{
	__raw_writel(val, info->regs + reg);
}