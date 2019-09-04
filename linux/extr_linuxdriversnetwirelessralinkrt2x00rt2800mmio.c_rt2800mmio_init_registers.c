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
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_CTRL ; 
 int /*<<< orphan*/  AUX_CTRL_FORCE_PCIE_CLK ; 
 int /*<<< orphan*/  AUX_CTRL_WAKE_PCIE_EN ; 
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_RESET_BBP ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_RESET_CSR ; 
 int /*<<< orphan*/  PBF_SYS_CTRL ; 
 int /*<<< orphan*/  PWR_PIN_CFG ; 
 int /*<<< orphan*/  RT3090 ; 
 int /*<<< orphan*/  RT3390 ; 
 int /*<<< orphan*/  RT3572 ; 
 int /*<<< orphan*/  RT3593 ; 
 int /*<<< orphan*/  RT5390 ; 
 int /*<<< orphan*/  RT5392 ; 
 int /*<<< orphan*/  RT5592 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DRX_IDX0 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX0 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX1 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX2 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX3 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX4 ; 
 int /*<<< orphan*/  WPDMA_RST_IDX_DTX_IDX5 ; 
 scalar_t__ rt2x00_is_pcie (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 

int rt2800mmio_init_registers(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	/*
	 * Reset DMA indexes
	 */
	reg = rt2x00mmio_register_read(rt2x00dev, WPDMA_RST_IDX);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX0, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX1, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX2, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX3, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX4, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DTX_IDX5, 1);
	rt2x00_set_field32(&reg, WPDMA_RST_IDX_DRX_IDX0, 1);
	rt2x00mmio_register_write(rt2x00dev, WPDMA_RST_IDX, reg);

	rt2x00mmio_register_write(rt2x00dev, PBF_SYS_CTRL, 0x00000e1f);
	rt2x00mmio_register_write(rt2x00dev, PBF_SYS_CTRL, 0x00000e00);

	if (rt2x00_is_pcie(rt2x00dev) &&
	    (rt2x00_rt(rt2x00dev, RT3090) ||
	     rt2x00_rt(rt2x00dev, RT3390) ||
	     rt2x00_rt(rt2x00dev, RT3572) ||
	     rt2x00_rt(rt2x00dev, RT3593) ||
	     rt2x00_rt(rt2x00dev, RT5390) ||
	     rt2x00_rt(rt2x00dev, RT5392) ||
	     rt2x00_rt(rt2x00dev, RT5592))) {
		reg = rt2x00mmio_register_read(rt2x00dev, AUX_CTRL);
		rt2x00_set_field32(&reg, AUX_CTRL_FORCE_PCIE_CLK, 1);
		rt2x00_set_field32(&reg, AUX_CTRL_WAKE_PCIE_EN, 1);
		rt2x00mmio_register_write(rt2x00dev, AUX_CTRL, reg);
	}

	rt2x00mmio_register_write(rt2x00dev, PWR_PIN_CFG, 0x00000003);

	reg = 0;
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_CSR, 1);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_RESET_BBP, 1);
	rt2x00mmio_register_write(rt2x00dev, MAC_SYS_CTRL, reg);

	rt2x00mmio_register_write(rt2x00dev, MAC_SYS_CTRL, 0x00000000);

	return 0;
}