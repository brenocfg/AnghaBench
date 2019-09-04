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
struct dio200_board {int /*<<< orphan*/  has_clk_gat_sce; scalar_t__ is_pcie; } ;
struct comedi_subdevice {struct comedi_8254* private; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct dio200_board* board_ptr; } ;
struct comedi_8254 {unsigned int* gate_src; unsigned int* clock_src; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 131 
#define  INSN_CONFIG_GET_GATE_SRC 130 
#define  INSN_CONFIG_SET_CLOCK_SRC 129 
#define  INSN_CONFIG_SET_GATE_SRC 128 
 unsigned int* clock_period ; 
 int /*<<< orphan*/  dio200_subdev_8254_set_clock_src (struct comedi_device*,struct comedi_subdevice*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dio200_subdev_8254_set_gate_src (struct comedi_device*,struct comedi_subdevice*,unsigned int,unsigned int) ; 

__attribute__((used)) static int dio200_subdev_8254_config(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	const struct dio200_board *board = dev->board_ptr;
	struct comedi_8254 *i8254 = s->private;
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int max_src = board->is_pcie ? 31 : 7;
	unsigned int src;

	if (!board->has_clk_gat_sce)
		return -EINVAL;

	switch (data[0]) {
	case INSN_CONFIG_SET_GATE_SRC:
		src = data[2];
		if (src > max_src)
			return -EINVAL;

		dio200_subdev_8254_set_gate_src(dev, s, chan, src);
		i8254->gate_src[chan] = src;
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		data[2] = i8254->gate_src[chan];
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		src = data[1];
		if (src > max_src)
			return -EINVAL;

		dio200_subdev_8254_set_clock_src(dev, s, chan, src);
		i8254->clock_src[chan] = src;
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		data[1] = i8254->clock_src[chan];
		data[2] = clock_period[i8254->clock_src[chan]];
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}