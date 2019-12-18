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
 int /*<<< orphan*/  kern_unmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_mnt ; 
 int /*<<< orphan*/  test_type ; 
 int /*<<< orphan*/  unregister_filesystem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_destroy_test_fs(void)
{
	kern_unmount(test_mnt);
	unregister_filesystem(&test_type);
}