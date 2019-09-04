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

/* Variables and functions */
 int /*<<< orphan*/  RPMSG_DEV_MAX ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpmsg_chrdev_driver ; 
 int /*<<< orphan*/  rpmsg_class ; 
 int /*<<< orphan*/  rpmsg_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_rpmsg_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rpmsg_chrdev_exit(void)
{
	unregister_rpmsg_driver(&rpmsg_chrdev_driver);
	class_destroy(rpmsg_class);
	unregister_chrdev_region(rpmsg_major, RPMSG_DEV_MAX);
}