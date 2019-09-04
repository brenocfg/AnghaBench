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
struct soundbus_dev {int /*<<< orphan*/  ofdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_device_unregister (int /*<<< orphan*/ *) ; 

void soundbus_remove_one(struct soundbus_dev *dev)
{
	of_device_unregister(&dev->ofdev);
}