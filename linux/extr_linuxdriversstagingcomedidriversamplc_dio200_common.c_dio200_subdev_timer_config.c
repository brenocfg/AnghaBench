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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 130 
#define  INSN_CONFIG_RESET 129 
#define  INSN_CONFIG_SET_CLOCK_SRC 128 
 int /*<<< orphan*/  dio200_subdev_timer_get_clock_src (struct comedi_device*,struct comedi_subdevice*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  dio200_subdev_timer_reset (struct comedi_device*,struct comedi_subdevice*) ; 
 int dio200_subdev_timer_set_clock_src (struct comedi_device*,struct comedi_subdevice*,unsigned int) ; 

__attribute__((used)) static int dio200_subdev_timer_config(struct comedi_device *dev,
				      struct comedi_subdevice *s,
				      struct comedi_insn *insn,
				      unsigned int *data)
{
	int ret = 0;

	switch (data[0]) {
	case INSN_CONFIG_RESET:
		dio200_subdev_timer_reset(dev, s);
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		ret = dio200_subdev_timer_set_clock_src(dev, s, data[1]);
		if (ret < 0)
			ret = -EINVAL;
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		dio200_subdev_timer_get_clock_src(dev, s, &data[1], &data[2]);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret < 0 ? ret : insn->n;
}