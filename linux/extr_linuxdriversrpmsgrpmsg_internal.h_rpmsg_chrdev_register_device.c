#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {char* driver_override; TYPE_1__ id; } ;

/* Variables and functions */
 int rpmsg_register_device (struct rpmsg_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int rpmsg_chrdev_register_device(struct rpmsg_device *rpdev)
{
	strcpy(rpdev->id.name, "rpmsg_chrdev");
	rpdev->driver_override = "rpmsg_chrdev";

	return rpmsg_register_device(rpdev);
}