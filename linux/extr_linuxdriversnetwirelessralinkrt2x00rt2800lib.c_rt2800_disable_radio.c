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
 int /*<<< orphan*/  MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_RX ; 
 int /*<<< orphan*/  MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  rt2800_disable_wpdma (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_wait_wpdma_ready (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_disable_radio(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	rt2800_disable_wpdma(rt2x00dev);

	/* Wait for DMA, ignore error */
	rt2800_wait_wpdma_ready(rt2x00dev);

	reg = rt2800_register_read(rt2x00dev, MAC_SYS_CTRL);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_TX, 0);
	rt2x00_set_field32(&reg, MAC_SYS_CTRL_ENABLE_RX, 0);
	rt2800_register_write(rt2x00dev, MAC_SYS_CTRL, reg);
}