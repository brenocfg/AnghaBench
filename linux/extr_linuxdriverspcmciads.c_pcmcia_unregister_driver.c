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
struct pcmcia_driver {int /*<<< orphan*/  drv; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_free_dynids (struct pcmcia_driver*) ; 
 int /*<<< orphan*/  pcmcia_remove_newid_file (struct pcmcia_driver*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void pcmcia_unregister_driver(struct pcmcia_driver *driver)
{
	pr_debug("unregistering driver %s\n", driver->name);
	pcmcia_remove_newid_file(driver);
	driver_unregister(&driver->drv);
	pcmcia_free_dynids(driver);
}