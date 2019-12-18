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
struct qnx6_sb_info {int dummy; } ;
struct qnx6_dir_entry {int /*<<< orphan*/  de_inode; int /*<<< orphan*/  de_fname; } ;

/* Variables and functions */
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int fs32_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned qnx6_match(struct super_block *s, int len, const char *name,
			struct qnx6_dir_entry *de)
{
	struct qnx6_sb_info *sbi = QNX6_SB(s);
	if (memcmp(name, de->de_fname, len) == 0)
		return fs32_to_cpu(sbi, de->de_inode);
	return 0;
}