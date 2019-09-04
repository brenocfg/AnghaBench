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
typedef  int /*<<< orphan*/  u32 ;
struct bcm2835aux_spi {unsigned int regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void bcm2835aux_wr(struct bcm2835aux_spi *bs, unsigned reg,
				 u32 val)
{
	writel(val, bs->regs + reg);
}