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
struct ni_private {unsigned int clock_ns; unsigned int pwm_up_count; unsigned int pwm_down_count; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
#define  CMDF_ROUND_DOWN 132 
#define  CMDF_ROUND_NEAREST 131 
#define  CMDF_ROUND_UP 130 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EAGAIN ; 
 int EINVAL ; 
#define  INSN_CONFIG_GET_PWM_OUTPUT 129 
#define  INSN_CONFIG_PWM_OUTPUT 128 
 int NI_M_CAL_PWM_HIGH_TIME (unsigned int) ; 
 int NI_M_CAL_PWM_LOW_TIME (unsigned int) ; 
 int /*<<< orphan*/  NI_M_CAL_PWM_REG ; 
 int ni_get_pwm_config (struct comedi_device*,unsigned int*) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_m_series_pwm_config(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	struct ni_private *devpriv = dev->private;
	unsigned int up_count, down_count;

	switch (data[0]) {
	case INSN_CONFIG_PWM_OUTPUT:
		switch (data[1]) {
		case CMDF_ROUND_NEAREST:
			up_count = DIV_ROUND_CLOSEST(data[2],
						     devpriv->clock_ns);
			break;
		case CMDF_ROUND_DOWN:
			up_count = data[2] / devpriv->clock_ns;
			break;
		case CMDF_ROUND_UP:
			up_count =
			    DIV_ROUND_UP(data[2], devpriv->clock_ns);
			break;
		default:
			return -EINVAL;
		}
		switch (data[3]) {
		case CMDF_ROUND_NEAREST:
			down_count = DIV_ROUND_CLOSEST(data[4],
						       devpriv->clock_ns);
			break;
		case CMDF_ROUND_DOWN:
			down_count = data[4] / devpriv->clock_ns;
			break;
		case CMDF_ROUND_UP:
			down_count =
			    DIV_ROUND_UP(data[4], devpriv->clock_ns);
			break;
		default:
			return -EINVAL;
		}
		if (up_count * devpriv->clock_ns != data[2] ||
		    down_count * devpriv->clock_ns != data[4]) {
			data[2] = up_count * devpriv->clock_ns;
			data[4] = down_count * devpriv->clock_ns;
			return -EAGAIN;
		}
		ni_writel(dev, NI_M_CAL_PWM_HIGH_TIME(up_count) |
			       NI_M_CAL_PWM_LOW_TIME(down_count),
			  NI_M_CAL_PWM_REG);
		devpriv->pwm_up_count = up_count;
		devpriv->pwm_down_count = down_count;
		return 5;
	case INSN_CONFIG_GET_PWM_OUTPUT:
		return ni_get_pwm_config(dev, data);
	default:
		return -EINVAL;
	}
	return 0;
}