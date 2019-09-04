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
 int /*<<< orphan*/  NUM_MINORS ; 
 int /*<<< orphan*/  cap_class ; 
 int /*<<< orphan*/  cap_dev_num ; 
 int /*<<< orphan*/  cap_minors_map ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cap_exit(void)
{
	unregister_chrdev_region(cap_dev_num, NUM_MINORS);
	class_destroy(cap_class);
	ida_destroy(&cap_minors_map);
}