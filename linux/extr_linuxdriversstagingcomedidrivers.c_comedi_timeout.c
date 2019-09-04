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
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_TIMEOUT_MS ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int comedi_timeout(struct comedi_device *dev,
		   struct comedi_subdevice *s,
		   struct comedi_insn *insn,
		   int (*cb)(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn,
			     unsigned long context),
		   unsigned long context)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(COMEDI_TIMEOUT_MS);
	int ret;

	while (time_before(jiffies, timeout)) {
		ret = cb(dev, s, insn, context);
		if (ret != -EBUSY)
			return ret;	/* success (0) or non EBUSY errno */
		cpu_relax();
	}
	return -ETIMEDOUT;
}