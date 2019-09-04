#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {scalar_t__ convert_src; int convert_arg; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_TIMER ; 
 unsigned int comedi_bytes_per_sample (struct comedi_subdevice*) ; 

__attribute__((used)) static unsigned int labpc_suggest_transfer_size(struct comedi_device *dev,
						struct comedi_subdevice *s,
						unsigned int maxbytes)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int sample_size = comedi_bytes_per_sample(s);
	unsigned int size;
	unsigned int freq;

	if (cmd->convert_src == TRIG_TIMER)
		freq = 1000000000 / cmd->convert_arg;
	else
		/* return some default value */
		freq = 0xffffffff;

	/* make buffer fill in no more than 1/3 second */
	size = (freq / 3) * sample_size;

	/* set a minimum and maximum size allowed */
	if (size > maxbytes)
		size = maxbytes;
	else if (size < sample_size)
		size = sample_size;

	return size;
}