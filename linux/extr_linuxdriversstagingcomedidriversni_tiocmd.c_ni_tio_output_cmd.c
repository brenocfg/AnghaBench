#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct {TYPE_2__* counter_dev; } ;
struct comedi_subdevice {struct ni_gpct* private; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ni_tio_output_cmd(struct comedi_subdevice *s)
{
	struct ni_gpct *counter = s->private;

	dev_err(counter->counter_dev->dev->class_dev,
		"output commands not yet implemented.\n");
	return -ENOTSUPP;
}