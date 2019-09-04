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
struct pcmcia_driver {int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_new_id ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pcmcia_remove_newid_file(struct pcmcia_driver *drv)
{
	driver_remove_file(&drv->drv, &driver_attr_new_id);
}