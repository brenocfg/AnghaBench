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
struct me_private_data {scalar_t__ plx_regbase; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; scalar_t__ mmio; struct me_private_data* private; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ PLX9052_INTCSR ; 
 int PLX9052_INTCSR_LI1ENAB ; 
 int PLX9052_INTCSR_LI1POL ; 
 unsigned int PLX9052_INTCSR_LI2STAT ; 
 int PLX9052_INTCSR_PCIENAB ; 
 scalar_t__ XILINX_DOWNLOAD_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  writeb (int const,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int me2600_xilinx_download(struct comedi_device *dev,
				  const u8 *data, size_t size,
				  unsigned long context)
{
	struct me_private_data *devpriv = dev->private;
	unsigned int value;
	unsigned int file_length;
	unsigned int i;

	/* disable irq's on PLX */
	writel(0x00, devpriv->plx_regbase + PLX9052_INTCSR);

	/* First, make a dummy read to reset xilinx */
	value = readw(dev->mmio + XILINX_DOWNLOAD_RESET);

	/* Wait until reset is over */
	sleep(1);

	/* Write a dummy value to Xilinx */
	writeb(0x00, dev->mmio + 0x0);
	sleep(1);

	/*
	 * Format of the firmware
	 * Build longs from the byte-wise coded header
	 * Byte 1-3:   length of the array
	 * Byte 4-7:   version
	 * Byte 8-11:  date
	 * Byte 12-15: reserved
	 */
	if (size < 16)
		return -EINVAL;

	file_length = (((unsigned int)data[0] & 0xff) << 24) +
	    (((unsigned int)data[1] & 0xff) << 16) +
	    (((unsigned int)data[2] & 0xff) << 8) +
	    ((unsigned int)data[3] & 0xff);

	/*
	 * Loop for writing firmware byte by byte to xilinx
	 * Firmware data start at offset 16
	 */
	for (i = 0; i < file_length; i++)
		writeb((data[16 + i] & 0xff), dev->mmio + 0x0);

	/* Write 5 dummy values to xilinx */
	for (i = 0; i < 5; i++)
		writeb(0x00, dev->mmio + 0x0);

	/* Test if there was an error during download -> INTB was thrown */
	value = readl(devpriv->plx_regbase + PLX9052_INTCSR);
	if (value & PLX9052_INTCSR_LI2STAT) {
		/* Disable interrupt */
		writel(0x00, devpriv->plx_regbase + PLX9052_INTCSR);
		dev_err(dev->class_dev, "Xilinx download failed\n");
		return -EIO;
	}

	/* Wait until the Xilinx is ready for real work */
	sleep(1);

	/* Enable PLX-Interrupts */
	writel(PLX9052_INTCSR_LI1ENAB |
	       PLX9052_INTCSR_LI1POL |
	       PLX9052_INTCSR_PCIENAB,
	       devpriv->plx_regbase + PLX9052_INTCSR);

	return 0;
}