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
struct comedi_subdevice {int index; int /*<<< orphan*/  io_bits; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int INSN_CONFIG_DIO_INPUT ; 
 int comedi_dio_insn_config (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmmio_dio_write (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcmmio_dio_insn_config(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	/* subdevice 2 uses ports 0-2, subdevice 3 uses ports 3-5 */
	int port = s->index == 2 ? 0 : 3;
	int ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0);
	if (ret)
		return ret;

	if (data[0] == INSN_CONFIG_DIO_INPUT)
		pcmmio_dio_write(dev, s->io_bits, 0, port);

	return insn->n;
}