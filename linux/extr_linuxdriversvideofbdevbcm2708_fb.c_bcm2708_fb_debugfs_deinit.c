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
struct bcm2708_fb {int /*<<< orphan*/ * debugfs_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm2708_fb_debugfs_deinit(struct bcm2708_fb *fb)
{
	debugfs_remove_recursive(fb->debugfs_dir);
	fb->debugfs_dir = NULL;
}