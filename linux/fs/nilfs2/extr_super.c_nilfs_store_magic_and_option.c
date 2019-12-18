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
struct the_nilfs {void* ns_watermark; void* ns_interval; void* ns_resgid; void* ns_resuid; } ;
struct super_block {int /*<<< orphan*/  s_flags; void* s_magic; struct the_nilfs* s_fs_info; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_c_block_max; int /*<<< orphan*/  s_c_interval; int /*<<< orphan*/  s_def_resgid; int /*<<< orphan*/  s_def_resuid; int /*<<< orphan*/  s_magic; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SB_NOATIME ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_set_default_options (struct super_block*,struct nilfs_super_block*) ; 
 int /*<<< orphan*/  parse_options (char*,struct super_block*,int /*<<< orphan*/ ) ; 

int nilfs_store_magic_and_option(struct super_block *sb,
				 struct nilfs_super_block *sbp,
				 char *data)
{
	struct the_nilfs *nilfs = sb->s_fs_info;

	sb->s_magic = le16_to_cpu(sbp->s_magic);

	/* FS independent flags */
#ifdef NILFS_ATIME_DISABLE
	sb->s_flags |= SB_NOATIME;
#endif

	nilfs_set_default_options(sb, sbp);

	nilfs->ns_resuid = le16_to_cpu(sbp->s_def_resuid);
	nilfs->ns_resgid = le16_to_cpu(sbp->s_def_resgid);
	nilfs->ns_interval = le32_to_cpu(sbp->s_c_interval);
	nilfs->ns_watermark = le32_to_cpu(sbp->s_c_block_max);

	return !parse_options(data, sb, 0) ? -EINVAL : 0;
}