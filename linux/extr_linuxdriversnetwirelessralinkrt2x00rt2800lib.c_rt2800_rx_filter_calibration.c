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
typedef  int u8 ;
struct rt2x00_dev {struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {void* bbp26; void* bbp25; void* calibration_bw40; void* calibration_bw20; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP4_BANDWIDTH ; 
 int /*<<< orphan*/  RFCSR22_BASEBAND_LOOPBACK ; 
 int /*<<< orphan*/  RT3070 ; 
 void* rt2800_bbp_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 void* rt2800_init_rx_filter (struct rt2x00_dev*,int,int) ; 
 int rt2800_rfcsr_read (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_rx_filter_calibration(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	u8 filter_tgt_bw20;
	u8 filter_tgt_bw40;
	u8 rfcsr, bbp;

	/*
	 * TODO: sync filter_tgt values with vendor driver
	 */
	if (rt2x00_rt(rt2x00dev, RT3070)) {
		filter_tgt_bw20 = 0x16;
		filter_tgt_bw40 = 0x19;
	} else {
		filter_tgt_bw20 = 0x13;
		filter_tgt_bw40 = 0x15;
	}

	drv_data->calibration_bw20 =
		rt2800_init_rx_filter(rt2x00dev, false, filter_tgt_bw20);
	drv_data->calibration_bw40 =
		rt2800_init_rx_filter(rt2x00dev, true, filter_tgt_bw40);

	/*
	 * Save BBP 25 & 26 values for later use in channel switching (for 3052)
	 */
	drv_data->bbp25 = rt2800_bbp_read(rt2x00dev, 25);
	drv_data->bbp26 = rt2800_bbp_read(rt2x00dev, 26);

	/*
	 * Set back to initial state
	 */
	rt2800_bbp_write(rt2x00dev, 24, 0);

	rfcsr = rt2800_rfcsr_read(rt2x00dev, 22);
	rt2x00_set_field8(&rfcsr, RFCSR22_BASEBAND_LOOPBACK, 0);
	rt2800_rfcsr_write(rt2x00dev, 22, rfcsr);

	/*
	 * Set BBP back to BW20
	 */
	bbp = rt2800_bbp_read(rt2x00dev, 4);
	rt2x00_set_field8(&bbp, BBP4_BANDWIDTH, 0);
	rt2800_bbp_write(rt2x00dev, 4, bbp);
}