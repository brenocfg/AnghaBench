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
struct nubus_driver {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 

void nubus_driver_unregister(struct nubus_driver *ndrv)
{
	driver_unregister(&ndrv->driver);
}