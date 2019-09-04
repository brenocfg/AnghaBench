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
struct comedi_device {int /*<<< orphan*/  board_name; int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  request_region (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

int __comedi_request_region(struct comedi_device *dev,
			    unsigned long start, unsigned long len)
{
	if (!start) {
		dev_warn(dev->class_dev,
			 "%s: a I/O base address must be specified\n",
			 dev->board_name);
		return -EINVAL;
	}

	if (!request_region(start, len, dev->board_name)) {
		dev_warn(dev->class_dev, "%s: I/O port conflict (%#lx,%lu)\n",
			 dev->board_name, start, len);
		return -EIO;
	}

	return 0;
}