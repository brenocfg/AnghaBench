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
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 

__attribute__((used)) static void rt2800_init_bbp_305x_soc(struct rt2x00_dev *rt2x00dev)
{
	rt2800_bbp_write(rt2x00dev, 31, 0x08);

	rt2800_bbp_write(rt2x00dev, 65, 0x2c);
	rt2800_bbp_write(rt2x00dev, 66, 0x38);

	rt2800_bbp_write(rt2x00dev, 69, 0x12);
	rt2800_bbp_write(rt2x00dev, 73, 0x10);

	rt2800_bbp_write(rt2x00dev, 70, 0x0a);

	rt2800_bbp_write(rt2x00dev, 78, 0x0e);
	rt2800_bbp_write(rt2x00dev, 80, 0x08);

	rt2800_bbp_write(rt2x00dev, 82, 0x62);

	rt2800_bbp_write(rt2x00dev, 83, 0x6a);

	rt2800_bbp_write(rt2x00dev, 84, 0x99);

	rt2800_bbp_write(rt2x00dev, 86, 0x00);

	rt2800_bbp_write(rt2x00dev, 91, 0x04);

	rt2800_bbp_write(rt2x00dev, 92, 0x00);

	rt2800_bbp_write(rt2x00dev, 103, 0xc0);

	rt2800_bbp_write(rt2x00dev, 105, 0x01);

	rt2800_bbp_write(rt2x00dev, 106, 0x35);
}