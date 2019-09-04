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
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  INT_MASK_CSR_PRE_TBTT ; 
 int /*<<< orphan*/  rt2800mmio_enable_interrupt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_pretbtt (struct rt2x00_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2800mmio_pretbtt_tasklet(unsigned long data)
{
	struct rt2x00_dev *rt2x00dev = (struct rt2x00_dev *)data;
	rt2x00lib_pretbtt(rt2x00dev);
	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_interrupt(rt2x00dev, INT_MASK_CSR_PRE_TBTT);
}