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
struct ni_gpct_device {int* regs; int /*<<< orphan*/  variant; } ;
struct ni_gpct {unsigned int counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 unsigned int CR_EDGE ; 
 unsigned int CR_INVERT ; 
 int EINVAL ; 
 unsigned int GI_BITS_TO_GATE (unsigned int) ; 
 unsigned int GI_BITS_TO_GATE2 (int) ; 
 int GI_GATE2_MODE ; 
 int GI_GATE2_POL_INVERT ; 
 unsigned int GI_GATE_POL_INVERT ; 
 unsigned int GI_GATING_DISABLED ; 
 unsigned int GI_GATING_MODE_MASK ; 
 unsigned int GI_LEVEL_GATING ; 
 size_t NITIO_GATE2_REG (unsigned int) ; 
 unsigned int NITIO_INPUT_SEL_REG (unsigned int) ; 
 unsigned int NITIO_MODE_REG (unsigned int) ; 
 unsigned int NI_GPCT_DISABLED_GATE_SELECT ; 
 int ni_660x_gate2_to_generic_gate (unsigned int,unsigned int*) ; 
 int ni_660x_gate_to_generic_gate (unsigned int,unsigned int*) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_m_gate2_to_generic_gate (unsigned int,unsigned int*) ; 
 int ni_m_gate_to_generic_gate (unsigned int,unsigned int*) ; 
 unsigned int ni_tio_get_soft_copy (struct ni_gpct*,unsigned int) ; 

__attribute__((used)) static int ni_tio_get_gate_src(struct ni_gpct *counter, unsigned int gate_index,
			       unsigned int *gate_source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned int cidx = counter->counter_index;
	unsigned int mode;
	unsigned int reg;
	unsigned int gate;
	int ret;

	mode = ni_tio_get_soft_copy(counter, NITIO_MODE_REG(cidx));
	if (((mode & GI_GATING_MODE_MASK) == GI_GATING_DISABLED) ||
	    (gate_index == 1 &&
	     !(counter_dev->regs[NITIO_GATE2_REG(cidx)] & GI_GATE2_MODE))) {
		*gate_source = NI_GPCT_DISABLED_GATE_SELECT;
		return 0;
	}

	switch (gate_index) {
	case 0:
		reg = NITIO_INPUT_SEL_REG(cidx);
		gate = GI_BITS_TO_GATE(ni_tio_get_soft_copy(counter, reg));

		switch (counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
		default:
			ret = ni_m_gate_to_generic_gate(gate, gate_source);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_gate_to_generic_gate(gate, gate_source);
			break;
		}
		if (ret)
			return ret;
		if (mode & GI_GATE_POL_INVERT)
			*gate_source |= CR_INVERT;
		if ((mode & GI_GATING_MODE_MASK) != GI_LEVEL_GATING)
			*gate_source |= CR_EDGE;
		break;
	case 1:
		reg = NITIO_GATE2_REG(cidx);
		gate = GI_BITS_TO_GATE2(counter_dev->regs[reg]);

		switch (counter_dev->variant) {
		case ni_gpct_variant_e_series:
		case ni_gpct_variant_m_series:
		default:
			ret = ni_m_gate2_to_generic_gate(gate, gate_source);
			break;
		case ni_gpct_variant_660x:
			ret = ni_660x_gate2_to_generic_gate(gate, gate_source);
			break;
		}
		if (ret)
			return ret;
		if (counter_dev->regs[reg] & GI_GATE2_POL_INVERT)
			*gate_source |= CR_INVERT;
		/* second gate can't have edge/level mode set independently */
		if ((mode & GI_GATING_MODE_MASK) != GI_LEVEL_GATING)
			*gate_source |= CR_EDGE;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}