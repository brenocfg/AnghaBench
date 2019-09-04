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
struct super_block {int dummy; } ;
struct jffs2_sb_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (struct super_block*) ; 
 int jffs2_do_remount_fs (struct super_block*,int*,char*) ; 
 int jffs2_parse_options (struct jffs2_sb_info*,char*) ; 
 int /*<<< orphan*/  sync_filesystem (struct super_block*) ; 

__attribute__((used)) static int jffs2_remount_fs(struct super_block *sb, int *flags, char *data)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(sb);
	int err;

	sync_filesystem(sb);
	err = jffs2_parse_options(c, data);
	if (err)
		return -EINVAL;

	return jffs2_do_remount_fs(sb, flags, data);
}