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
struct file {struct comedi_file* private_data; } ;
struct comedi_file {scalar_t__ last_attached; scalar_t__ last_detach_count; struct comedi_device* dev; } ;
struct comedi_device {scalar_t__ attached; scalar_t__ detach_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_file_reset (struct file*) ; 

__attribute__((used)) static void comedi_file_check(struct file *file)
{
	struct comedi_file *cfp = file->private_data;
	struct comedi_device *dev = cfp->dev;

	if (cfp->last_attached != dev->attached ||
	    cfp->last_detach_count != dev->detach_count)
		comedi_file_reset(file);
}