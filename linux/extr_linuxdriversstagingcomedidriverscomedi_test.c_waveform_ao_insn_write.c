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
struct waveform_private {unsigned int* ao_loopbacks; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {struct waveform_private* private; } ;

/* Variables and functions */
 int CR_CHAN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waveform_ao_insn_write(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn, unsigned int *data)
{
	struct waveform_private *devpriv = dev->private;
	int i, chan = CR_CHAN(insn->chanspec);

	for (i = 0; i < insn->n; i++)
		devpriv->ao_loopbacks[chan] = data[i];

	return insn->n;
}