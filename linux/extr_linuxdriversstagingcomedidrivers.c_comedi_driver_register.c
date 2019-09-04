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
struct comedi_driver {struct comedi_driver* next; } ;

/* Variables and functions */
 struct comedi_driver* comedi_drivers ; 
 int /*<<< orphan*/  comedi_drivers_list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int comedi_driver_register(struct comedi_driver *driver)
{
	mutex_lock(&comedi_drivers_list_lock);
	driver->next = comedi_drivers;
	comedi_drivers = driver;
	mutex_unlock(&comedi_drivers_list_lock);

	return 0;
}