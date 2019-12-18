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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fatent_operations {int /*<<< orphan*/  (* ent_put ) (struct fat_entry*,int) ;} ;
struct fat_entry {int /*<<< orphan*/  nr_bhs; int /*<<< orphan*/  bhs; } ;
struct TYPE_2__ {struct fatent_operations* fatent_ops; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int fat_mirror_bhs (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fat_sync_bhs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fat_entry*,int) ; 

int fat_ent_write(struct inode *inode, struct fat_entry *fatent,
		  int new, int wait)
{
	struct super_block *sb = inode->i_sb;
	const struct fatent_operations *ops = MSDOS_SB(sb)->fatent_ops;
	int err;

	ops->ent_put(fatent, new);
	if (wait) {
		err = fat_sync_bhs(fatent->bhs, fatent->nr_bhs);
		if (err)
			return err;
	}
	return fat_mirror_bhs(sb, fatent->bhs, fatent->nr_bhs);
}