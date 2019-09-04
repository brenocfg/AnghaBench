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
 int /*<<< orphan*/  delayed_superblock_init ; 
 int /*<<< orphan*/  iterate_supers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void selinux_complete_init(void)
{
	pr_debug("SELinux:  Completing initialization.\n");

	/* Set up any superblocks initialized prior to the policy load. */
	pr_debug("SELinux:  Setting up existing superblocks.\n");
	iterate_supers(delayed_superblock_init, NULL);
}