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
 int /*<<< orphan*/  MULTIQ3_BP_RESET ; 
 int /*<<< orphan*/  MULTIQ3_CLOCK_DATA ; 
 int /*<<< orphan*/  MULTIQ3_CLOCK_SETUP ; 
 int /*<<< orphan*/  MULTIQ3_CNTR_RESET ; 
 int MULTIQ3_CTRL_EN ; 
 int MULTIQ3_CTRL_E_CHAN (unsigned int) ; 
 int /*<<< orphan*/  MULTIQ3_EFLAG_RESET ; 
 scalar_t__ MULTIQ3_ENC_CTRL_REG ; 
 scalar_t__ MULTIQ3_ENC_DATA_REG ; 
 int /*<<< orphan*/  MULTIQ3_INPUT_SETUP ; 
 int /*<<< orphan*/  MULTIQ3_QUAD_X4 ; 
 int /*<<< orphan*/  multiq3_set_ctrl (struct comedi_device*,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void multiq3_encoder_reset(struct comedi_device *dev,
				  unsigned int chan)
{
	multiq3_set_ctrl(dev, MULTIQ3_CTRL_EN | MULTIQ3_CTRL_E_CHAN(chan));
	outb(MULTIQ3_EFLAG_RESET, dev->iobase + MULTIQ3_ENC_CTRL_REG);
	outb(MULTIQ3_BP_RESET, dev->iobase + MULTIQ3_ENC_CTRL_REG);
	outb(MULTIQ3_CLOCK_DATA, dev->iobase + MULTIQ3_ENC_DATA_REG);
	outb(MULTIQ3_CLOCK_SETUP, dev->iobase + MULTIQ3_ENC_CTRL_REG);
	outb(MULTIQ3_INPUT_SETUP, dev->iobase + MULTIQ3_ENC_CTRL_REG);
	outb(MULTIQ3_QUAD_X4, dev->iobase + MULTIQ3_ENC_CTRL_REG);
	outb(MULTIQ3_CNTR_RESET, dev->iobase + MULTIQ3_ENC_CTRL_REG);
}