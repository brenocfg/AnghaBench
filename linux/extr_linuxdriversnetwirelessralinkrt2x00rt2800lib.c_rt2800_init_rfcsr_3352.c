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
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_PA_TX0 ; 
 int /*<<< orphan*/  CAPABILITY_EXTERNAL_PA_TX1 ; 
 int /*<<< orphan*/  RFCSR34_TX0_EXT_PA ; 
 int /*<<< orphan*/  RFCSR34_TX1_EXT_PA ; 
 int /*<<< orphan*/  RFCSR41_BIT1 ; 
 int /*<<< orphan*/  RFCSR41_BIT4 ; 
 int /*<<< orphan*/  RFCSR42_BIT1 ; 
 int /*<<< orphan*/  RFCSR42_BIT4 ; 
 int /*<<< orphan*/  RFCSR50_TX0_EXT_PA ; 
 int /*<<< orphan*/  RFCSR50_TX1_EXT_PA ; 
 int /*<<< orphan*/  rt2800_led_open_drain_enable (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_normal_mode_setup_3xxx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rf_init_calibration (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rx_filter_calibration (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int*,int /*<<< orphan*/ ,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2800_init_rfcsr_3352(struct rt2x00_dev *rt2x00dev)
{
	int tx0_ext_pa = test_bit(CAPABILITY_EXTERNAL_PA_TX0,
				  &rt2x00dev->cap_flags);
	int tx1_ext_pa = test_bit(CAPABILITY_EXTERNAL_PA_TX1,
				  &rt2x00dev->cap_flags);
	u8 rfcsr;

	rt2800_rf_init_calibration(rt2x00dev, 30);

	rt2800_rfcsr_write(rt2x00dev, 0, 0xf0);
	rt2800_rfcsr_write(rt2x00dev, 1, 0x23);
	rt2800_rfcsr_write(rt2x00dev, 2, 0x50);
	rt2800_rfcsr_write(rt2x00dev, 3, 0x18);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x33);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 8, 0xf1);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 10, 0xd2);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x42);
	rt2800_rfcsr_write(rt2x00dev, 12, 0x1c);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x5a);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x01);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x45);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 21, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x10);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 33, 0x00);
	rfcsr = 0x01;
	if (tx0_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR34_TX0_EXT_PA, 1);
	if (tx1_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR34_TX1_EXT_PA, 1);
	rt2800_rfcsr_write(rt2x00dev, 34, rfcsr);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 36, 0xbd);
	rt2800_rfcsr_write(rt2x00dev, 37, 0x3c);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x5f);
	rt2800_rfcsr_write(rt2x00dev, 39, 0xc5);
	rt2800_rfcsr_write(rt2x00dev, 40, 0x33);
	rfcsr = 0x52;
	if (!tx0_ext_pa) {
		rt2x00_set_field8(&rfcsr, RFCSR41_BIT1, 1);
		rt2x00_set_field8(&rfcsr, RFCSR41_BIT4, 1);
	}
	rt2800_rfcsr_write(rt2x00dev, 41, rfcsr);
	rfcsr = 0x52;
	if (!tx1_ext_pa) {
		rt2x00_set_field8(&rfcsr, RFCSR42_BIT1, 1);
		rt2x00_set_field8(&rfcsr, RFCSR42_BIT4, 1);
	}
	rt2800_rfcsr_write(rt2x00dev, 42, rfcsr);
	rt2800_rfcsr_write(rt2x00dev, 43, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 44, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 45, 0xdb);
	rt2800_rfcsr_write(rt2x00dev, 46, 0xdd);
	rt2800_rfcsr_write(rt2x00dev, 47, 0x0d);
	rt2800_rfcsr_write(rt2x00dev, 48, 0x14);
	rt2800_rfcsr_write(rt2x00dev, 49, 0x00);
	rfcsr = 0x2d;
	if (tx0_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR50_TX0_EXT_PA, 1);
	if (tx1_ext_pa)
		rt2x00_set_field8(&rfcsr, RFCSR50_TX1_EXT_PA, 1);
	rt2800_rfcsr_write(rt2x00dev, 50, rfcsr);
	rt2800_rfcsr_write(rt2x00dev, 51, (tx0_ext_pa ? 0x52 : 0x7f));
	rt2800_rfcsr_write(rt2x00dev, 52, (tx0_ext_pa ? 0xc0 : 0x00));
	rt2800_rfcsr_write(rt2x00dev, 53, (tx0_ext_pa ? 0xd2 : 0x52));
	rt2800_rfcsr_write(rt2x00dev, 54, (tx0_ext_pa ? 0xc0 : 0x1b));
	rt2800_rfcsr_write(rt2x00dev, 55, (tx1_ext_pa ? 0x52 : 0x7f));
	rt2800_rfcsr_write(rt2x00dev, 56, (tx1_ext_pa ? 0xc0 : 0x00));
	rt2800_rfcsr_write(rt2x00dev, 57, (tx0_ext_pa ? 0x49 : 0x52));
	rt2800_rfcsr_write(rt2x00dev, 58, (tx1_ext_pa ? 0xc0 : 0x1b));
	rt2800_rfcsr_write(rt2x00dev, 59, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 60, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 63, 0x00);

	rt2800_rx_filter_calibration(rt2x00dev);
	rt2800_led_open_drain_enable(rt2x00dev);
	rt2800_normal_mode_setup_3xxx(rt2x00dev);
}