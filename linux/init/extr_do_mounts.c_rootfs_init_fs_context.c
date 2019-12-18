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
struct fs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TMPFS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tmpfs ; 
 int ramfs_init_fs_context (struct fs_context*) ; 
 int shmem_init_fs_context (struct fs_context*) ; 

__attribute__((used)) static int rootfs_init_fs_context(struct fs_context *fc)
{
	if (IS_ENABLED(CONFIG_TMPFS) && is_tmpfs)
		return shmem_init_fs_context(fc);

	return ramfs_init_fs_context(fc);
}