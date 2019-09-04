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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 unsigned int REGISTER_BUSY_COUNT ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int /*<<< orphan*/  WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rt2800_wait_wpdma_ready(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u32 reg;

	/*
	 * Some devices are really slow to respond here. Wait a whole second
	 * before timing out.
	 */
	for (i = 0; i < REGISTER_BUSY_COUNT; i++) {
		reg = rt2800_register_read(rt2x00dev, WPDMA_GLO_CFG);
		if (!rt2x00_get_field32(reg, WPDMA_GLO_CFG_TX_DMA_BUSY) &&
		    !rt2x00_get_field32(reg, WPDMA_GLO_CFG_RX_DMA_BUSY))
			return 0;

		msleep(10);
	}

	rt2x00_err(rt2x00dev, "WPDMA TX/RX busy [0x%08x]\n", reg);
	return -EACCES;
}