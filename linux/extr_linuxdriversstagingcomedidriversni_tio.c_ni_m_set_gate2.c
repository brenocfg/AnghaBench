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
struct ni_gpct_device {int /*<<< orphan*/ * regs; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 int /*<<< orphan*/  GI_GATE2_MODE ; 
 int /*<<< orphan*/  GI_GATE2_SEL (unsigned int) ; 
 int /*<<< orphan*/  GI_GATE2_SEL_MASK ; 
 unsigned int NITIO_GATE2_REG (unsigned int) ; 
 int /*<<< orphan*/  ni_tio_write (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ni_m_set_gate2(struct ni_gpct *counter, unsigned int gate_source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int chan = CR_CHAN(gate_source);
	unsigned int gate2_reg = NITIO_GATE2_REG(cidx);
	unsigned int gate2_sel;

	/*
	 * FIXME: We don't know what the m-series second gate codes are,
	 * so we'll just pass the bits through for now.
	 */
	switch (chan) {
	default:
		gate2_sel = chan & 0x1f;
		break;
	}
	counter_dev->regs[gate2_reg] |= GI_GATE2_MODE;
	counter_dev->regs[gate2_reg] &= ~GI_GATE2_SEL_MASK;
	counter_dev->regs[gate2_reg] |= GI_GATE2_SEL(gate2_sel);
	ni_tio_write(counter, counter_dev->regs[gate2_reg], gate2_reg);
	return 0;
}