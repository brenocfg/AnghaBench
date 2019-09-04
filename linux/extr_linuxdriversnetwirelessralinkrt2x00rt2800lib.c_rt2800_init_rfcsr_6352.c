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
struct rt2x00_dev {int freq_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800_bw_filter_calibration (struct rt2x00_dev*,int) ; 
 scalar_t__ rt2800_clk_is_20mhz (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write_bank (struct rt2x00_dev*,int,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write_chanreg (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write_dccal (struct rt2x00_dev*,int,int) ; 

__attribute__((used)) static void rt2800_init_rfcsr_6352(struct rt2x00_dev *rt2x00dev)
{
	/* Initialize RF central register to default value */
	rt2800_rfcsr_write(rt2x00dev, 0, 0x02);
	rt2800_rfcsr_write(rt2x00dev, 1, 0x03);
	rt2800_rfcsr_write(rt2x00dev, 2, 0x33);
	rt2800_rfcsr_write(rt2x00dev, 3, 0xFF);
	rt2800_rfcsr_write(rt2x00dev, 4, 0x0C);
	rt2800_rfcsr_write(rt2x00dev, 5, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 6, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 7, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 8, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 9, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 10, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 11, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 12, rt2x00dev->freq_offset);
	rt2800_rfcsr_write(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x40);
	rt2800_rfcsr_write(rt2x00dev, 15, 0x22);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x4C);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 20, 0xA0);
	rt2800_rfcsr_write(rt2x00dev, 21, 0x12);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x07);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x13);
	rt2800_rfcsr_write(rt2x00dev, 24, 0xFE);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x24);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x7A);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 29, 0x05);
	rt2800_rfcsr_write(rt2x00dev, 30, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 31, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 32, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 34, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 35, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 37, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 38, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 40, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 41, 0xD0);
	rt2800_rfcsr_write(rt2x00dev, 42, 0x5B);
	rt2800_rfcsr_write(rt2x00dev, 43, 0x00);

	rt2800_rfcsr_write(rt2x00dev, 11, 0x21);
	if (rt2800_clk_is_20mhz(rt2x00dev))
		rt2800_rfcsr_write(rt2x00dev, 13, 0x03);
	else
		rt2800_rfcsr_write(rt2x00dev, 13, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 14, 0x7C);
	rt2800_rfcsr_write(rt2x00dev, 16, 0x80);
	rt2800_rfcsr_write(rt2x00dev, 17, 0x99);
	rt2800_rfcsr_write(rt2x00dev, 18, 0x99);
	rt2800_rfcsr_write(rt2x00dev, 19, 0x09);
	rt2800_rfcsr_write(rt2x00dev, 20, 0x50);
	rt2800_rfcsr_write(rt2x00dev, 21, 0xB0);
	rt2800_rfcsr_write(rt2x00dev, 22, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 23, 0x06);
	rt2800_rfcsr_write(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 26, 0x5D);
	rt2800_rfcsr_write(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write(rt2x00dev, 28, 0x61);
	rt2800_rfcsr_write(rt2x00dev, 29, 0xB5);
	rt2800_rfcsr_write(rt2x00dev, 43, 0x02);

	rt2800_rfcsr_write(rt2x00dev, 28, 0x62);
	rt2800_rfcsr_write(rt2x00dev, 29, 0xAD);
	rt2800_rfcsr_write(rt2x00dev, 39, 0x80);

	/* Initialize RF channel register to default value */
	rt2800_rfcsr_write_chanreg(rt2x00dev, 0, 0x03);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 1, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 2, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 3, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 5, 0x08);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 6, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 7, 0x51);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 8, 0x53);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 9, 0x16);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 10, 0x61);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 11, 0x53);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 12, 0x22);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 13, 0x3D);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 14, 0x06);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 15, 0x13);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 16, 0x22);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 17, 0x27);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 18, 0x02);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 19, 0xA7);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 20, 0x01);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 21, 0x52);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 22, 0x80);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 23, 0xB3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 24, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 25, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 27, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 28, 0x5C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 29, 0x6B);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 30, 0x6B);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 31, 0x31);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 32, 0x5D);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 33, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 34, 0xE6);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 35, 0x55);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 36, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 37, 0xBB);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 38, 0xB3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 39, 0xB3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 40, 0x03);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 43, 0xB3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 44, 0xD3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 45, 0xD5);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 46, 0x07);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 47, 0x68);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 48, 0xEF);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 49, 0x1C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 54, 0x07);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 55, 0xA8);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 56, 0x85);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 57, 0x10);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 58, 0x07);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 59, 0x6A);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 60, 0x85);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 61, 0x10);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 62, 0x1C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 63, 0x00);

	rt2800_rfcsr_write_bank(rt2x00dev, 6, 45, 0xC5);

	rt2800_rfcsr_write_chanreg(rt2x00dev, 9, 0x47);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 10, 0x71);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 11, 0x33);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 14, 0x0E);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 17, 0x23);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 19, 0xA4);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 20, 0x02);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 21, 0x12);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 28, 0x1C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 29, 0xEB);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 32, 0x7D);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 34, 0xD6);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 36, 0x08);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 38, 0xB4);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 43, 0xD3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 44, 0xB3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 45, 0xD5);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 46, 0x27);
	rt2800_rfcsr_write_bank(rt2x00dev, 4, 47, 0x67);
	rt2800_rfcsr_write_bank(rt2x00dev, 6, 47, 0x69);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 48, 0xFF);
	rt2800_rfcsr_write_bank(rt2x00dev, 4, 54, 0x27);
	rt2800_rfcsr_write_bank(rt2x00dev, 6, 54, 0x20);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 55, 0x66);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 56, 0xFF);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 57, 0x1C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 58, 0x20);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 59, 0x6B);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 60, 0xF7);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 61, 0x09);

	rt2800_rfcsr_write_chanreg(rt2x00dev, 10, 0x51);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 14, 0x06);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 19, 0xA7);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 28, 0x2C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 55, 0x64);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 8, 0x51);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 9, 0x36);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 11, 0x53);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 14, 0x16);

	rt2800_rfcsr_write_chanreg(rt2x00dev, 47, 0x6C);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 48, 0xFC);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 49, 0x1F);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 54, 0x27);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 55, 0x66);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 59, 0x6B);

	/* Initialize RF channel register for DRQFN */
	rt2800_rfcsr_write_chanreg(rt2x00dev, 43, 0xD3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 44, 0xE3);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 45, 0xE5);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 47, 0x28);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 55, 0x68);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 56, 0xF7);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 58, 0x02);
	rt2800_rfcsr_write_chanreg(rt2x00dev, 60, 0xC7);

	/* Initialize RF DC calibration register to default value */
	rt2800_rfcsr_write_dccal(rt2x00dev, 0, 0x47);
	rt2800_rfcsr_write_dccal(rt2x00dev, 1, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 2, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 3, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 4, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 6, 0x10);
	rt2800_rfcsr_write_dccal(rt2x00dev, 7, 0x10);
	rt2800_rfcsr_write_dccal(rt2x00dev, 8, 0x04);
	rt2800_rfcsr_write_dccal(rt2x00dev, 9, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 10, 0x07);
	rt2800_rfcsr_write_dccal(rt2x00dev, 11, 0x01);
	rt2800_rfcsr_write_dccal(rt2x00dev, 12, 0x07);
	rt2800_rfcsr_write_dccal(rt2x00dev, 13, 0x07);
	rt2800_rfcsr_write_dccal(rt2x00dev, 14, 0x07);
	rt2800_rfcsr_write_dccal(rt2x00dev, 15, 0x20);
	rt2800_rfcsr_write_dccal(rt2x00dev, 16, 0x22);
	rt2800_rfcsr_write_dccal(rt2x00dev, 17, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 18, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 19, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 20, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 21, 0xF1);
	rt2800_rfcsr_write_dccal(rt2x00dev, 22, 0x11);
	rt2800_rfcsr_write_dccal(rt2x00dev, 23, 0x02);
	rt2800_rfcsr_write_dccal(rt2x00dev, 24, 0x41);
	rt2800_rfcsr_write_dccal(rt2x00dev, 25, 0x20);
	rt2800_rfcsr_write_dccal(rt2x00dev, 26, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 27, 0xD7);
	rt2800_rfcsr_write_dccal(rt2x00dev, 28, 0xA2);
	rt2800_rfcsr_write_dccal(rt2x00dev, 29, 0x20);
	rt2800_rfcsr_write_dccal(rt2x00dev, 30, 0x49);
	rt2800_rfcsr_write_dccal(rt2x00dev, 31, 0x20);
	rt2800_rfcsr_write_dccal(rt2x00dev, 32, 0x04);
	rt2800_rfcsr_write_dccal(rt2x00dev, 33, 0xF1);
	rt2800_rfcsr_write_dccal(rt2x00dev, 34, 0xA1);
	rt2800_rfcsr_write_dccal(rt2x00dev, 35, 0x01);
	rt2800_rfcsr_write_dccal(rt2x00dev, 41, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 42, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 43, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 44, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 45, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 46, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 47, 0x3E);
	rt2800_rfcsr_write_dccal(rt2x00dev, 48, 0x3D);
	rt2800_rfcsr_write_dccal(rt2x00dev, 49, 0x3E);
	rt2800_rfcsr_write_dccal(rt2x00dev, 50, 0x3D);
	rt2800_rfcsr_write_dccal(rt2x00dev, 51, 0x3E);
	rt2800_rfcsr_write_dccal(rt2x00dev, 52, 0x3D);
	rt2800_rfcsr_write_dccal(rt2x00dev, 53, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 54, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 55, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 56, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 57, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 58, 0x10);
	rt2800_rfcsr_write_dccal(rt2x00dev, 59, 0x10);
	rt2800_rfcsr_write_dccal(rt2x00dev, 60, 0x0A);
	rt2800_rfcsr_write_dccal(rt2x00dev, 61, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 62, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 63, 0x00);

	rt2800_rfcsr_write_dccal(rt2x00dev, 3, 0x08);
	rt2800_rfcsr_write_dccal(rt2x00dev, 4, 0x04);
	rt2800_rfcsr_write_dccal(rt2x00dev, 5, 0x20);

	rt2800_rfcsr_write_dccal(rt2x00dev, 5, 0x00);
	rt2800_rfcsr_write_dccal(rt2x00dev, 17, 0x7C);

	rt2800_bw_filter_calibration(rt2x00dev, true);
	rt2800_bw_filter_calibration(rt2x00dev, false);
}