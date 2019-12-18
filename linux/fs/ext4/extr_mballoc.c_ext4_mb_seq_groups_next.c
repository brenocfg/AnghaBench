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
struct seq_file {int /*<<< orphan*/  file; } ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ ext4_group_t ;

/* Variables and functions */
 struct super_block* PDE_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *ext4_mb_seq_groups_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct super_block *sb = PDE_DATA(file_inode(seq->file));
	ext4_group_t group;

	++*pos;
	if (*pos < 0 || *pos >= ext4_get_groups_count(sb))
		return NULL;
	group = *pos + 1;
	return (void *) ((unsigned long) group);
}