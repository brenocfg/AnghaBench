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
struct rt2x00_dev {int beacon_int; int /*<<< orphan*/  flags; scalar_t__ intf_ap_count; struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int tbtt_tick; } ;

/* Variables and functions */
 int BCN_TBTT_OFFSET ; 
 int /*<<< orphan*/  BCN_TIME_CFG ; 
 int /*<<< orphan*/  BCN_TIME_CFG_BEACON_INTERVAL ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  INT_MASK_CSR_TBTT ; 
 int /*<<< orphan*/  rt2800mmio_enable_interrupt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00lib_beacondone (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2800mmio_tbtt_tasklet(unsigned long data)
{
	struct rt2x00_dev *rt2x00dev = (struct rt2x00_dev *)data;
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u32 reg;

	rt2x00lib_beacondone(rt2x00dev);

	if (rt2x00dev->intf_ap_count) {
		/*
		 * The rt2800pci hardware tbtt timer is off by 1us per tbtt
		 * causing beacon skew and as a result causing problems with
		 * some powersaving clients over time. Shorten the beacon
		 * interval every 64 beacons by 64us to mitigate this effect.
		 */
		if (drv_data->tbtt_tick == (BCN_TBTT_OFFSET - 2)) {
			reg = rt2x00mmio_register_read(rt2x00dev, BCN_TIME_CFG);
			rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL,
					   (rt2x00dev->beacon_int * 16) - 1);
			rt2x00mmio_register_write(rt2x00dev, BCN_TIME_CFG, reg);
		} else if (drv_data->tbtt_tick == (BCN_TBTT_OFFSET - 1)) {
			reg = rt2x00mmio_register_read(rt2x00dev, BCN_TIME_CFG);
			rt2x00_set_field32(&reg, BCN_TIME_CFG_BEACON_INTERVAL,
					   (rt2x00dev->beacon_int * 16));
			rt2x00mmio_register_write(rt2x00dev, BCN_TIME_CFG, reg);
		}
		drv_data->tbtt_tick++;
		drv_data->tbtt_tick %= BCN_TBTT_OFFSET;
	}

	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2800mmio_enable_interrupt(rt2x00dev, INT_MASK_CSR_TBTT);
}