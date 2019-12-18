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
struct super_block {size_t s_blocksize; } ;
struct nilfs_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;
struct nilfs_dat_info {int /*<<< orphan*/  shadow; int /*<<< orphan*/  palloc_cache; TYPE_1__ mi; } ;
struct lock_class_key {int dummy; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I_NEW ; 
 int /*<<< orphan*/  KERN_ERR ; 
 struct nilfs_dat_info* NILFS_DAT_I (struct inode*) ; 
 int /*<<< orphan*/  NILFS_DAT_INO ; 
 int /*<<< orphan*/  NILFS_MDT_GFP ; 
 size_t NILFS_MIN_DAT_ENTRY_SIZE ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 struct inode* nilfs_iget_locked (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_init (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_mdt_setup_shadow_map (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,size_t) ; 
 int nilfs_palloc_init_blockgroup (struct inode*,size_t) ; 
 int /*<<< orphan*/  nilfs_palloc_setup_cache (struct inode*,int /*<<< orphan*/ *) ; 
 int nilfs_read_inode_common (struct inode*,struct nilfs_inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

int nilfs_dat_read(struct super_block *sb, size_t entry_size,
		   struct nilfs_inode *raw_inode, struct inode **inodep)
{
	static struct lock_class_key dat_lock_key;
	struct inode *dat;
	struct nilfs_dat_info *di;
	int err;

	if (entry_size > sb->s_blocksize) {
		nilfs_msg(sb, KERN_ERR, "too large DAT entry size: %zu bytes",
			  entry_size);
		return -EINVAL;
	} else if (entry_size < NILFS_MIN_DAT_ENTRY_SIZE) {
		nilfs_msg(sb, KERN_ERR, "too small DAT entry size: %zu bytes",
			  entry_size);
		return -EINVAL;
	}

	dat = nilfs_iget_locked(sb, NULL, NILFS_DAT_INO);
	if (unlikely(!dat))
		return -ENOMEM;
	if (!(dat->i_state & I_NEW))
		goto out;

	err = nilfs_mdt_init(dat, NILFS_MDT_GFP, sizeof(*di));
	if (err)
		goto failed;

	err = nilfs_palloc_init_blockgroup(dat, entry_size);
	if (err)
		goto failed;

	di = NILFS_DAT_I(dat);
	lockdep_set_class(&di->mi.mi_sem, &dat_lock_key);
	nilfs_palloc_setup_cache(dat, &di->palloc_cache);
	nilfs_mdt_setup_shadow_map(dat, &di->shadow);

	err = nilfs_read_inode_common(dat, raw_inode);
	if (err)
		goto failed;

	unlock_new_inode(dat);
 out:
	*inodep = dat;
	return 0;
 failed:
	iget_failed(dat);
	return err;
}