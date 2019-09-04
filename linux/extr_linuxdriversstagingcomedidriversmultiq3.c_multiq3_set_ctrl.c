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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 unsigned int MULTIQ3_CTRL_CLK ; 
 scalar_t__ MULTIQ3_CTRL_REG ; 
 unsigned int MULTIQ3_CTRL_SH ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static void multiq3_set_ctrl(struct comedi_device *dev, unsigned int bits)
{
	/*
	 * According to the programming manual, the SH and CLK bits should
	 * be kept high at all times.
	 */
	outw(MULTIQ3_CTRL_SH | MULTIQ3_CTRL_CLK | bits,
	     dev->iobase + MULTIQ3_CTRL_REG);
}