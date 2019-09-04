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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_cmd {scalar_t__ stop_src; unsigned long long scan_end_arg; int /*<<< orphan*/  stop_arg; } ;
struct comedi_async {int /*<<< orphan*/  scan_progress; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ TRIG_COUNT ; 
 unsigned long long __comedi_nscans_left (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 unsigned long long comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 

unsigned int comedi_nsamples_left(struct comedi_subdevice *s,
				  unsigned int nsamples)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned long long scans_left;
	unsigned long long samples_left;

	if (cmd->stop_src != TRIG_COUNT)
		return nsamples;

	scans_left = __comedi_nscans_left(s, cmd->stop_arg);
	if (!scans_left)
		return 0;

	samples_left = scans_left * cmd->scan_end_arg -
		comedi_bytes_to_samples(s, async->scan_progress);

	if (samples_left < nsamples)
		return samples_left;
	return nsamples;
}