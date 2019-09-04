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
#define  INSN_CONFIG_BLOCK_SIZE 128 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,int) ; 
 int gsc_hpdi_setup_dma_descriptors (struct comedi_device*,unsigned int) ; 

__attribute__((used)) static int gsc_hpdi_dio_insn_config(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	int ret;

	switch (data[0]) {
	case INSN_CONFIG_BLOCK_SIZE:
		ret = gsc_hpdi_setup_dma_descriptors(dev, data[1]);
		if (ret)
			return ret;

		data[1] = ret;
		break;
	default:
		ret = comedi_dio_insn_config(dev, s, insn, data, 0xffffffff);
		if (ret)
			return ret;
		break;
	}

	return insn->n;
}