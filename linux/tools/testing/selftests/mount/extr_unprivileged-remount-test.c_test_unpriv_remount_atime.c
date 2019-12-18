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
 int test_unpriv_remount (char*,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static bool test_unpriv_remount_atime(int mount_flags, int invalid_flags)
{
	return test_unpriv_remount("ramfs", NULL, mount_flags, mount_flags,
				   invalid_flags);
}