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
struct device {int dummy; } ;

/* Variables and functions */
#define  PDM_CLK_CTRL 139 
#define  PDM_CTRL0 138 
#define  PDM_CTRL1 137 
#define  PDM_DATA_VALID 136 
#define  PDM_DMA_CTRL 135 
#define  PDM_FIFO_CTRL 134 
#define  PDM_HPF_CTRL 133 
#define  PDM_INT_CLR 132 
#define  PDM_INT_EN 131 
#define  PDM_INT_ST 130 
#define  PDM_SYSCONFIG 129 
#define  PDM_VERSION 128 

__attribute__((used)) static bool rockchip_pdm_rd_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case PDM_SYSCONFIG:
	case PDM_CTRL0:
	case PDM_CTRL1:
	case PDM_CLK_CTRL:
	case PDM_HPF_CTRL:
	case PDM_FIFO_CTRL:
	case PDM_DMA_CTRL:
	case PDM_INT_EN:
	case PDM_INT_CLR:
	case PDM_INT_ST:
	case PDM_DATA_VALID:
	case PDM_VERSION:
		return true;
	default:
		return false;
	}
}