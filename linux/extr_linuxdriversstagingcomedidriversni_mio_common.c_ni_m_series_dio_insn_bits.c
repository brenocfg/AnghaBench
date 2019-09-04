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
struct comedi_subdevice {int /*<<< orphan*/  state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI_M_DIO_REG ; 
 scalar_t__ comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 unsigned int ni_readl (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_m_series_dio_insn_bits(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		ni_writel(dev, s->state, NI_M_DIO_REG);

	data[1] = ni_readl(dev, NI_M_DIO_REG);

	return insn->n;
}