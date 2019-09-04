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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5350 ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_init_bbp_3352(struct rt2x00_dev *rt2x00dev)
{
	rt2800_bbp_write(rt2x00dev, 3, 0x00);
	rt2800_bbp_write(rt2x00dev, 4, 0x50);

	rt2800_bbp_write(rt2x00dev, 31, 0x08);

	rt2800_bbp_write(rt2x00dev, 47, 0x48);

	rt2800_bbp_write(rt2x00dev, 65, 0x2c);
	rt2800_bbp_write(rt2x00dev, 66, 0x38);

	rt2800_bbp_write(rt2x00dev, 68, 0x0b);

	rt2800_bbp_write(rt2x00dev, 69, 0x12);
	rt2800_bbp_write(rt2x00dev, 73, 0x13);
	rt2800_bbp_write(rt2x00dev, 75, 0x46);
	rt2800_bbp_write(rt2x00dev, 76, 0x28);

	rt2800_bbp_write(rt2x00dev, 77, 0x59);

	rt2800_bbp_write(rt2x00dev, 70, 0x0a);

	rt2800_bbp_write(rt2x00dev, 78, 0x0e);
	rt2800_bbp_write(rt2x00dev, 80, 0x08);
	rt2800_bbp_write(rt2x00dev, 81, 0x37);

	rt2800_bbp_write(rt2x00dev, 82, 0x62);

	if (rt2x00_rt(rt2x00dev, RT5350)) {
		rt2800_bbp_write(rt2x00dev, 83, 0x7a);
		rt2800_bbp_write(rt2x00dev, 84, 0x9a);
	} else {
		rt2800_bbp_write(rt2x00dev, 83, 0x6a);
		rt2800_bbp_write(rt2x00dev, 84, 0x99);
	}

	rt2800_bbp_write(rt2x00dev, 86, 0x38);

	rt2800_bbp_write(rt2x00dev, 88, 0x90);

	rt2800_bbp_write(rt2x00dev, 91, 0x04);

	rt2800_bbp_write(rt2x00dev, 92, 0x02);

	rt2800_bbp_write(rt2x00dev, 103, 0xc0);

	rt2800_bbp_write(rt2x00dev, 104, 0x92);

	if (rt2x00_rt(rt2x00dev, RT5350)) {
		rt2800_bbp_write(rt2x00dev, 105, 0x3c);
		rt2800_bbp_write(rt2x00dev, 106, 0x03);
	} else {
		rt2800_bbp_write(rt2x00dev, 105, 0x34);
		rt2800_bbp_write(rt2x00dev, 106, 0x05);
	}

	rt2800_bbp_write(rt2x00dev, 120, 0x50);

	rt2800_bbp_write(rt2x00dev, 137, 0x0f);

	rt2800_bbp_write(rt2x00dev, 163, 0xbd);
	/* Set ITxBF timeout to 0x9c40=1000msec */
	rt2800_bbp_write(rt2x00dev, 179, 0x02);
	rt2800_bbp_write(rt2x00dev, 180, 0x00);
	rt2800_bbp_write(rt2x00dev, 182, 0x40);
	rt2800_bbp_write(rt2x00dev, 180, 0x01);
	rt2800_bbp_write(rt2x00dev, 182, 0x9c);
	rt2800_bbp_write(rt2x00dev, 179, 0x00);
	/* Reprogram the inband interface to put right values in RXWI */
	rt2800_bbp_write(rt2x00dev, 142, 0x04);
	rt2800_bbp_write(rt2x00dev, 143, 0x3b);
	rt2800_bbp_write(rt2x00dev, 142, 0x06);
	rt2800_bbp_write(rt2x00dev, 143, 0xa0);
	rt2800_bbp_write(rt2x00dev, 142, 0x07);
	rt2800_bbp_write(rt2x00dev, 143, 0xa1);
	rt2800_bbp_write(rt2x00dev, 142, 0x08);
	rt2800_bbp_write(rt2x00dev, 143, 0xa2);

	rt2800_bbp_write(rt2x00dev, 148, 0xc8);

	if (rt2x00_rt(rt2x00dev, RT5350)) {
		/* Antenna Software OFDM */
		rt2800_bbp_write(rt2x00dev, 150, 0x40);
		/* Antenna Software CCK */
		rt2800_bbp_write(rt2x00dev, 151, 0x30);
		rt2800_bbp_write(rt2x00dev, 152, 0xa3);
		/* Clear previously selected antenna */
		rt2800_bbp_write(rt2x00dev, 154, 0);
	}
}