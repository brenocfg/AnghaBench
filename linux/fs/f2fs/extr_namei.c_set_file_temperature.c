#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb_lock; TYPE_1__* raw_super; } ;
struct TYPE_2__ {int hot_ext_count; int /*<<< orphan*/  extension_count; int /*<<< orphan*/  extension_list; } ;

/* Variables and functions */
 size_t F2FS_EXTENSION_LEN ; 
 int /*<<< orphan*/ * __u8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extlist ; 
 int /*<<< orphan*/  file_set_cold (struct inode*) ; 
 int /*<<< orphan*/  file_set_hot (struct inode*) ; 
 scalar_t__ is_extension_exist (unsigned char const*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_file_temperature(struct f2fs_sb_info *sbi, struct inode *inode,
		const unsigned char *name)
{
	__u8 (*extlist)[F2FS_EXTENSION_LEN] = sbi->raw_super->extension_list;
	int i, cold_count, hot_count;

	down_read(&sbi->sb_lock);

	cold_count = le32_to_cpu(sbi->raw_super->extension_count);
	hot_count = sbi->raw_super->hot_ext_count;

	for (i = 0; i < cold_count + hot_count; i++) {
		if (is_extension_exist(name, extlist[i]))
			break;
	}

	up_read(&sbi->sb_lock);

	if (i == cold_count + hot_count)
		return;

	if (i < cold_count)
		file_set_cold(inode);
	else
		file_set_hot(inode);
}