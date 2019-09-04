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
struct ep93xx_i2s_info {unsigned int regs; } ;

/* Variables and functions */
 int __raw_readl (unsigned int) ; 

__attribute__((used)) static inline unsigned ep93xx_i2s_read_reg(struct ep93xx_i2s_info *info,
					   unsigned reg)
{
	return __raw_readl(info->regs + reg);
}