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
struct msdos_sb_info {int /*<<< orphan*/  inode_hash_lock; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_pos; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_I (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline loff_t fat_i_pos_read(struct msdos_sb_info *sbi,
					struct inode *inode)
{
	loff_t i_pos;
#if BITS_PER_LONG == 32
	spin_lock(&sbi->inode_hash_lock);
#endif
	i_pos = MSDOS_I(inode)->i_pos;
#if BITS_PER_LONG == 32
	spin_unlock(&sbi->inode_hash_lock);
#endif
	return i_pos;
}