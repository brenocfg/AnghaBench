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
 unsigned int C6XDIGIO_DATA_ENCODER ; 
 int /*<<< orphan*/  c6xdigio_get_encoder_bits (struct comedi_device*,unsigned int*,unsigned int,int) ; 
 int /*<<< orphan*/  c6xdigio_write_data (struct comedi_device*,int,int) ; 

__attribute__((used)) static int c6xdigio_encoder_read(struct comedi_device *dev,
				 unsigned int chan)
{
	unsigned int cmd = C6XDIGIO_DATA_ENCODER | C6XDIGIO_DATA_CHAN(chan);
	unsigned int val = 0;
	unsigned int bits;

	c6xdigio_write_data(dev, cmd, 0x00);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 0);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 3);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 6);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 9);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 12);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 15);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (1 << 2), 0x80);
	val |= (bits << 18);

	c6xdigio_get_encoder_bits(dev, &bits, cmd | (0 << 2), 0x00);
	val |= (bits << 21);

	c6xdigio_write_data(dev, 0x00, 0x80);

	return val;
}