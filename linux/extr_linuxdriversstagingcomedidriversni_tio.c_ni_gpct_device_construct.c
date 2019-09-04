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
struct ni_gpct_device {void (* write ) (struct ni_gpct*,unsigned int,int) ;unsigned int (* read ) (struct ni_gpct*,int) ;int variant; unsigned int num_counters; struct ni_gpct* counters; int /*<<< orphan*/  regs_lock; struct comedi_device* dev; } ;
struct ni_gpct {int /*<<< orphan*/  lock; struct ni_gpct_device* counter_dev; } ;
struct comedi_device {int dummy; } ;
typedef  enum ni_gpct_variant { ____Placeholder_ni_gpct_variant } ni_gpct_variant ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ni_gpct* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ni_gpct_device*) ; 
 struct ni_gpct_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ni_gpct_device *
ni_gpct_device_construct(struct comedi_device *dev,
			 void (*write)(struct ni_gpct *counter,
				       unsigned int value,
				       enum ni_gpct_register reg),
			 unsigned int (*read)(struct ni_gpct *counter,
					      enum ni_gpct_register reg),
			 enum ni_gpct_variant variant,
			 unsigned int num_counters)
{
	struct ni_gpct_device *counter_dev;
	struct ni_gpct *counter;
	unsigned int i;

	if (num_counters == 0)
		return NULL;

	counter_dev = kzalloc(sizeof(*counter_dev), GFP_KERNEL);
	if (!counter_dev)
		return NULL;

	counter_dev->dev = dev;
	counter_dev->write = write;
	counter_dev->read = read;
	counter_dev->variant = variant;

	spin_lock_init(&counter_dev->regs_lock);

	counter_dev->counters = kcalloc(num_counters, sizeof(*counter),
					GFP_KERNEL);
	if (!counter_dev->counters) {
		kfree(counter_dev);
		return NULL;
	}

	for (i = 0; i < num_counters; ++i) {
		counter = &counter_dev->counters[i];
		counter->counter_dev = counter_dev;
		spin_lock_init(&counter->lock);
	}
	counter_dev->num_counters = num_counters;

	return counter_dev;
}