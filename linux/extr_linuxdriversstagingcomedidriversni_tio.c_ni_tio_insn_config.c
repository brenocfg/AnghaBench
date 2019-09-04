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
struct ni_gpct {unsigned int counter_index; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int COMEDI_COUNTER_ARMED ; 
 unsigned int COMEDI_COUNTER_COUNTING ; 
 int EINVAL ; 
 unsigned int GI_ARMED (unsigned int) ; 
 unsigned int GI_COUNTING (unsigned int) ; 
#define  INSN_CONFIG_ARM 137 
#define  INSN_CONFIG_DISARM 136 
#define  INSN_CONFIG_GET_CLOCK_SRC 135 
#define  INSN_CONFIG_GET_COUNTER_STATUS 134 
#define  INSN_CONFIG_GET_GATE_SRC 133 
#define  INSN_CONFIG_RESET 132 
#define  INSN_CONFIG_SET_CLOCK_SRC 131 
#define  INSN_CONFIG_SET_COUNTER_MODE 130 
#define  INSN_CONFIG_SET_GATE_SRC 129 
#define  INSN_CONFIG_SET_OTHER_SRC 128 
 int /*<<< orphan*/  NITIO_SHARED_STATUS_REG (unsigned int) ; 
 int ni_tio_arm (struct ni_gpct*,int,unsigned int) ; 
 int ni_tio_get_clock_src (struct ni_gpct*,unsigned int*,unsigned int*) ; 
 int ni_tio_get_gate_src (struct ni_gpct*,unsigned int,unsigned int*) ; 
 unsigned int ni_tio_read (struct ni_gpct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_reset_count_and_disarm (struct ni_gpct*) ; 
 int ni_tio_set_clock_src (struct ni_gpct*,unsigned int,unsigned int) ; 
 int ni_tio_set_counter_mode (struct ni_gpct*,unsigned int) ; 
 int ni_tio_set_gate_src (struct ni_gpct*,unsigned int,unsigned int) ; 
 int ni_tio_set_other_src (struct ni_gpct*,unsigned int,unsigned int) ; 

int ni_tio_insn_config(struct comedi_device *dev,
		       struct comedi_subdevice *s,
		       struct comedi_insn *insn,
		       unsigned int *data)
{
	struct ni_gpct *counter = s->private;
	unsigned int cidx = counter->counter_index;
	unsigned int status;
	int ret = 0;

	switch (data[0]) {
	case INSN_CONFIG_SET_COUNTER_MODE:
		ret = ni_tio_set_counter_mode(counter, data[1]);
		break;
	case INSN_CONFIG_ARM:
		ret = ni_tio_arm(counter, true, data[1]);
		break;
	case INSN_CONFIG_DISARM:
		ret = ni_tio_arm(counter, false, 0);
		break;
	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = 0;
		status = ni_tio_read(counter, NITIO_SHARED_STATUS_REG(cidx));
		if (status & GI_ARMED(cidx)) {
			data[1] |= COMEDI_COUNTER_ARMED;
			if (status & GI_COUNTING(cidx))
				data[1] |= COMEDI_COUNTER_COUNTING;
		}
		data[2] = COMEDI_COUNTER_ARMED | COMEDI_COUNTER_COUNTING;
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		ret = ni_tio_set_clock_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		ret = ni_tio_get_clock_src(counter, &data[1], &data[2]);
		break;
	case INSN_CONFIG_SET_GATE_SRC:
		ret = ni_tio_set_gate_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		ret = ni_tio_get_gate_src(counter, data[1], &data[2]);
		break;
	case INSN_CONFIG_SET_OTHER_SRC:
		ret = ni_tio_set_other_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_RESET:
		ni_tio_reset_count_and_disarm(counter);
		break;
	default:
		return -EINVAL;
	}
	return ret ? ret : insn->n;
}