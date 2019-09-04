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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int C6XDIGIO_DATA_CHAN (unsigned int) ; 
 unsigned int C6XDIGIO_DATA_PWM ; 
 int /*<<< orphan*/  c6xdigio_write_data (struct comedi_device*,int,int) ; 

__attribute__((used)) static void c6xdigio_pwm_write(struct comedi_device *dev,
			       unsigned int chan, unsigned int val)
{
	unsigned int cmd = C6XDIGIO_DATA_PWM | C6XDIGIO_DATA_CHAN(chan);
	unsigned int bits;

	if (val > 498)
		val = 498;
	if (val < 2)
		val = 2;

	bits = (val >> 0) & 0x03;
	c6xdigio_write_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (val >> 2) & 0x03;
	c6xdigio_write_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (val >> 4) & 0x03;
	c6xdigio_write_data(dev, cmd | bits | (0 << 2), 0x00);
	bits = (val >> 6) & 0x03;
	c6xdigio_write_data(dev, cmd | bits | (1 << 2), 0x80);
	bits = (val >> 8) & 0x03;
	c6xdigio_write_data(dev, cmd | bits | (0 << 2), 0x00);

	c6xdigio_write_data(dev, 0x00, 0x80);
}