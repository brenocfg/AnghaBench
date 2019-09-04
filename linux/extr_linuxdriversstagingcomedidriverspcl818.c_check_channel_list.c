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
struct comedi_subdevice {int n_chan; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_AREF (unsigned int) ; 
 unsigned int CR_CHAN (unsigned int) ; 
 int /*<<< orphan*/  CR_RANGE (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_channel_list(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      unsigned int *chanlist, unsigned int n_chan)
{
	unsigned int chansegment[16];
	unsigned int i, nowmustbechan, seglen;

	/* correct channel and range number check itself comedi/range.c */
	if (n_chan < 1) {
		dev_err(dev->class_dev, "range/channel list is empty!\n");
		return 0;
	}

	if (n_chan > 1) {
		/*  first channel is every time ok */
		chansegment[0] = chanlist[0];
		/*  build part of chanlist */
		for (i = 1, seglen = 1; i < n_chan; i++, seglen++) {
			/* we detect loop, this must by finish */

			if (chanlist[0] == chanlist[i])
				break;
			nowmustbechan =
			    (CR_CHAN(chansegment[i - 1]) + 1) % s->n_chan;
			if (nowmustbechan != CR_CHAN(chanlist[i])) {
				/*  channel list isn't continuous :-( */
				dev_dbg(dev->class_dev,
					"channel list must be continuous! chanlist[%i]=%d but must be %d or %d!\n",
					i, CR_CHAN(chanlist[i]), nowmustbechan,
					CR_CHAN(chanlist[0]));
				return 0;
			}
			/*  well, this is next correct channel in list */
			chansegment[i] = chanlist[i];
		}

		/*  check whole chanlist */
		for (i = 0; i < n_chan; i++) {
			if (chanlist[i] != chansegment[i % seglen]) {
				dev_dbg(dev->class_dev,
					"bad channel or range number! chanlist[%i]=%d,%d,%d and not %d,%d,%d!\n",
					i, CR_CHAN(chansegment[i]),
					CR_RANGE(chansegment[i]),
					CR_AREF(chansegment[i]),
					CR_CHAN(chanlist[i % seglen]),
					CR_RANGE(chanlist[i % seglen]),
					CR_AREF(chansegment[i % seglen]));
				return 0;	/*  chan/gain list is strange */
			}
		}
	} else {
		seglen = 1;
	}
	return seglen;
}