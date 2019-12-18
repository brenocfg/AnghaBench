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
struct super_block {struct squashfs_sb_info* s_fs_info; } ;
struct squashfs_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 void* get_comp_opts (struct super_block*,unsigned short) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* squashfs_decompressor_create (struct squashfs_sb_info*,void*) ; 

void *squashfs_decompressor_setup(struct super_block *sb, unsigned short flags)
{
	struct squashfs_sb_info *msblk = sb->s_fs_info;
	void *stream, *comp_opts = get_comp_opts(sb, flags);

	if (IS_ERR(comp_opts))
		return comp_opts;

	stream = squashfs_decompressor_create(msblk, comp_opts);
	if (IS_ERR(stream))
		kfree(comp_opts);

	return stream;
}