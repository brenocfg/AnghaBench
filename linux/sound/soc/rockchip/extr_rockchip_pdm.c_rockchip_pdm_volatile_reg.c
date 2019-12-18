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
#define  PDM_FIFO_CTRL 132 
#define  PDM_INT_CLR 131 
#define  PDM_INT_ST 130 
#define  PDM_RXFIFO_DATA 129 
#define  PDM_SYSCONFIG 128 

__attribute__((used)) static bool rockchip_pdm_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case PDM_SYSCONFIG:
	case PDM_FIFO_CTRL:
	case PDM_INT_CLR:
	case PDM_INT_ST:
	case PDM_RXFIFO_DATA:
		return true;
	default:
		return false;
	}
}