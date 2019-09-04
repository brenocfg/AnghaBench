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
struct comedi_subdevice {scalar_t__ minor; int /*<<< orphan*/ * class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 scalar_t__ COMEDI_NUM_BOARD_MINORS ; 
 scalar_t__ COMEDI_NUM_MINORS ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  comedi_class ; 
 struct comedi_subdevice** comedi_subdevice_minor_table ; 
 int /*<<< orphan*/  comedi_subdevice_minor_table_lock ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void comedi_free_subdevice_minor(struct comedi_subdevice *s)
{
	unsigned int i;

	if (!s)
		return;
	if (s->minor < COMEDI_NUM_BOARD_MINORS ||
	    s->minor >= COMEDI_NUM_MINORS)
		return;

	i = s->minor - COMEDI_NUM_BOARD_MINORS;
	mutex_lock(&comedi_subdevice_minor_table_lock);
	if (s == comedi_subdevice_minor_table[i])
		comedi_subdevice_minor_table[i] = NULL;
	mutex_unlock(&comedi_subdevice_minor_table_lock);
	if (s->class_dev) {
		device_destroy(comedi_class, MKDEV(COMEDI_MAJOR, s->minor));
		s->class_dev = NULL;
	}
}