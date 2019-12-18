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
struct inode {int i_blocks; int i_size; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int mmu_private; scalar_t__ i_n_secs; } ;

/* Variables and functions */
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 TYPE_1__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_lock_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpfs_truncate_btree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hpfs_write_inode (struct inode*) ; 

void hpfs_truncate(struct inode *i)
{
	if (IS_IMMUTABLE(i)) return /*-EPERM*/;
	hpfs_lock_assert(i->i_sb);

	hpfs_i(i)->i_n_secs = 0;
	i->i_blocks = 1 + ((i->i_size + 511) >> 9);
	hpfs_i(i)->mmu_private = i->i_size;
	hpfs_truncate_btree(i->i_sb, i->i_ino, 1, ((i->i_size + 511) >> 9));
	hpfs_write_inode(i);
	hpfs_i(i)->i_n_secs = 0;
}