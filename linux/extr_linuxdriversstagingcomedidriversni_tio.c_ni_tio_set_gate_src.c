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
struct ni_gpct_device {int /*<<< orphan*/  variant; int /*<<< orphan*/ * regs; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int CR_CHAN (unsigned int) ; 
 unsigned int CR_EDGE ; 
 unsigned int CR_INVERT ; 
 int EINVAL ; 
 int /*<<< orphan*/  GI_GATE2_MODE ; 
 int /*<<< orphan*/  GI_GATE2_POL_INVERT ; 
 unsigned int GI_GATE_POL_INVERT ; 
 unsigned int GI_GATING_DISABLED ; 
 unsigned int GI_GATING_MODE_MASK ; 
 unsigned int GI_LEVEL_GATING ; 
 unsigned int GI_RISING_EDGE_GATING ; 
 unsigned int NITIO_GATE2_REG (unsigned int) ; 
 int /*<<< orphan*/  NITIO_MODE_REG (unsigned int) ; 
 unsigned int NI_GPCT_DISABLED_GATE_SELECT ; 
 int ni_660x_set_gate (struct ni_gpct*,unsigned int) ; 
 int ni_660x_set_gate2 (struct ni_gpct*,unsigned int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_m_set_gate (struct ni_gpct*,unsigned int) ; 
 int ni_m_set_gate2 (struct ni_gpct*,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_has_gate2_registers (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ni_tio_write (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int) ; 

int ni_tio_set_gate_src(struct ni_gpct *counter,
			unsigned int gate, unsigned int src)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int chan = CR_CHAN(src);
	unsigned int gate2_reg = NITIO_GATE2_REG(cidx);
	unsigned int mode = 0;

	switch (gate) {
	case 0:
		if (chan == NI_GPCT_DISABLED_GATE_SELECT) {
			ni_tio_set_bits(counter, NITIO_MODE_REG(cidx),
					GI_GATING_MODE_MASK,
					GI_GATING_DISABLED);
			return 0;
		}
		if (src & CR_INVERT)
			mode |= GI_GATE_POL_INVERT;
		if (src & CR_EDGE)
			mode |= GI_RISING_EDGE_GATING;
		else
			mode |= GI_LEVEL_GATING;
		ni_tio_set_bits(counter, NITIO_MODE_REG(cidx),
				GI_GATE_POL_INVERT | GI_GATING_MODE_MASK,
				mode);
		switch (counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
		default:
			return ni_m_set_gate(counter, src);
		case ni_gpct_variant_660x:
			return ni_660x_set_gate(counter, src);
		}
		break;
	case 1:
		if (!ni_tio_has_gate2_registers(counter_dev))
			return -EINVAL;

		if (chan == NI_GPCT_DISABLED_GATE_SELECT) {
			counter_dev->regs[gate2_reg] &= ~GI_GATE2_MODE;
			ni_tio_write(counter, counter_dev->regs[gate2_reg],
				     gate2_reg);
			return 0;
		}
		if (src & CR_INVERT)
			counter_dev->regs[gate2_reg] |= GI_GATE2_POL_INVERT;
		else
			counter_dev->regs[gate2_reg] &= ~GI_GATE2_POL_INVERT;
		switch (counter_dev->variant) {
		case ni_gpct_variant_m_series:
			return ni_m_set_gate2(counter, src);
		case ni_gpct_variant_660x:
			return ni_660x_set_gate2(counter, src);
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}