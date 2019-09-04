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
struct vfs_cap_data {int /*<<< orphan*/  magic_etc; } ;

/* Variables and functions */
 scalar_t__ VFS_CAP_REVISION_3 ; 
 size_t XATTR_CAPS_SZ_3 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ sansflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_v3header(size_t size, const struct vfs_cap_data *cap)
{
	if (size != XATTR_CAPS_SZ_3)
		return false;
	return sansflags(le32_to_cpu(cap->magic_etc)) == VFS_CAP_REVISION_3;
}