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
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMSG_NAME ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmsg_class ; 
 int /*<<< orphan*/  pmsg_major ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pstore_unregister_pmsg(void)
{
	device_destroy(pmsg_class, MKDEV(pmsg_major, 0));
	class_destroy(pmsg_class);
	unregister_chrdev(pmsg_major, PMSG_NAME);
}