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
struct fs_context {void* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfs_get_keyed_super ; 
 int vfs_get_super (struct fs_context*,int /*<<< orphan*/ ,int (*) (struct super_block*,struct fs_context*)) ; 

int get_tree_keyed(struct fs_context *fc,
		  int (*fill_super)(struct super_block *sb,
				    struct fs_context *fc),
		void *key)
{
	fc->s_fs_info = key;
	return vfs_get_super(fc, vfs_get_keyed_super, fill_super);
}