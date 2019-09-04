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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_GET_CLOCK_SRC 136 
#define  INSN_CONFIG_RESET 135 
#define  INSN_CONFIG_SET_CLOCK_SRC 134 
#define  KE_CLK_20MHZ 133 
#define  KE_CLK_4MHZ 132 
#define  KE_CLK_EXT 131 
#define  KE_OSC_SEL_20MHZ 130 
#define  KE_OSC_SEL_4MHZ 129 
#define  KE_OSC_SEL_EXT 128 
 scalar_t__ KE_OSC_SEL_REG ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  ke_counter_reset (struct comedi_device*) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int ke_counter_insn_config(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned char src;

	switch (data[0]) {
	case INSN_CONFIG_SET_CLOCK_SRC:
		switch (data[1]) {
		case KE_CLK_20MHZ:	/* default */
			src = KE_OSC_SEL_20MHZ;
			break;
		case KE_CLK_4MHZ:	/* option */
			src = KE_OSC_SEL_4MHZ;
			break;
		case KE_CLK_EXT:	/* Pin 21 on D-sub */
			src = KE_OSC_SEL_EXT;
			break;
		default:
			return -EINVAL;
		}
		outb(src, dev->iobase + KE_OSC_SEL_REG);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		src = inb(dev->iobase + KE_OSC_SEL_REG);
		switch (src) {
		case KE_OSC_SEL_20MHZ:
			data[1] = KE_CLK_20MHZ;
			data[2] = 50;	/* 50ns */
			break;
		case KE_OSC_SEL_4MHZ:
			data[1] = KE_CLK_4MHZ;
			data[2] = 250;	/* 250ns */
			break;
		case KE_OSC_SEL_EXT:
			data[1] = KE_CLK_EXT;
			data[2] = 0;	/* Unknown */
			break;
		default:
			return -EINVAL;
		}
		break;
	case INSN_CONFIG_RESET:
		ke_counter_reset(dev);
		break;
	default:
		return -EINVAL;
	}

	return insn->n;
}