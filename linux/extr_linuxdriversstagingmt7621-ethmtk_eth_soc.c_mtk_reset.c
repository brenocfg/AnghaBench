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
struct mtk_eth {int /*<<< orphan*/  ethsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSC_REG_RSTCTRL ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void mtk_reset(struct mtk_eth *eth, u32 reset_bits)
{
	u32 val;

	regmap_read(eth->ethsys, SYSC_REG_RSTCTRL, &val);
	val |= reset_bits;
	regmap_write(eth->ethsys, SYSC_REG_RSTCTRL, val);
	usleep_range(10, 20);
	val &= ~reset_bits;
	regmap_write(eth->ethsys, SYSC_REG_RSTCTRL, val);
	usleep_range(10, 20);
}