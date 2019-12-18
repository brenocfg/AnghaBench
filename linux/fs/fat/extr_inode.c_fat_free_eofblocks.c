#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_blocks; int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmu_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  cluster_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 TYPE_2__* MSDOS_I (struct inode*) ; 
 TYPE_1__* MSDOS_SB (int /*<<< orphan*/ ) ; 
 int __fat_write_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fat_truncate_blocks (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_needs_sync (struct inode*) ; 
 int round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fat_free_eofblocks(struct inode *inode)
{
	/* Release unwritten fallocated blocks on inode eviction. */
	if ((inode->i_blocks << 9) >
			round_up(MSDOS_I(inode)->mmu_private,
				MSDOS_SB(inode->i_sb)->cluster_size)) {
		int err;

		fat_truncate_blocks(inode, MSDOS_I(inode)->mmu_private);
		/* Fallocate results in updating the i_start/iogstart
		 * for the zero byte file. So, make it return to
		 * original state during evict and commit it to avoid
		 * any corruption on the next access to the cluster
		 * chain for the file.
		 */
		err = __fat_write_inode(inode, inode_needs_sync(inode));
		if (err) {
			fat_msg(inode->i_sb, KERN_WARNING, "Failed to "
					"update on disk inode for unused "
					"fallocated blocks, inode could be "
					"corrupted. Please run fsck");
		}

	}
}