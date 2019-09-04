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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ NI6527_FALLING_EDGE_REG (unsigned int) ; 
 scalar_t__ NI6527_RISING_EDGE_REG (unsigned int) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void ni6527_set_edge_detection(struct comedi_device *dev,
				      unsigned int mask,
				      unsigned int rising,
				      unsigned int falling)
{
	unsigned int i;

	rising &= mask;
	falling &= mask;
	for (i = 0; i < 2; i++) {
		if (mask & 0xff) {
			if (~mask & 0xff) {
				/* preserve rising-edge detection channels */
				rising |= readb(dev->mmio +
						NI6527_RISING_EDGE_REG(i)) &
					  (~mask & 0xff);
				/* preserve falling-edge detection channels */
				falling |= readb(dev->mmio +
						 NI6527_FALLING_EDGE_REG(i)) &
					   (~mask & 0xff);
			}
			/* update rising-edge detection channels */
			writeb(rising & 0xff,
			       dev->mmio + NI6527_RISING_EDGE_REG(i));
			/* update falling-edge detection channels */
			writeb(falling & 0xff,
			       dev->mmio + NI6527_FALLING_EDGE_REG(i));
		}
		rising >>= 8;
		falling >>= 8;
		mask >>= 8;
	}
}