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
struct comedi_device {int /*<<< orphan*/  minor; scalar_t__ class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_class ; 
 int /*<<< orphan*/  comedi_dev_put (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_device_cleanup (struct comedi_device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void comedi_free_board_dev(struct comedi_device *dev)
{
	if (dev) {
		comedi_device_cleanup(dev);
		if (dev->class_dev) {
			device_destroy(comedi_class,
				       MKDEV(COMEDI_MAJOR, dev->minor));
		}
		comedi_dev_put(dev);
	}
}