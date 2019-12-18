#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_blocksize_bits; } ;
struct kmem_cache {int dummy; } ;
struct ext4_sb_info {size_t s_group_info_size; int /*<<< orphan*/ * s_group_info; TYPE_1__* s_buddy_cache; } ;
struct ext4_group_desc {int dummy; } ;
typedef  size_t ext4_group_t ;
struct TYPE_6__ {scalar_t__ i_disksize; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_BAD_INO ; 
 TYPE_3__* EXT4_I (TYPE_1__*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_get_group_info (struct super_block*,size_t) ; 
 size_t ext4_get_groups_count (struct super_block*) ; 
 scalar_t__ ext4_mb_add_groupinfo (struct super_block*,size_t,struct ext4_group_desc*) ; 
 int ext4_mb_alloc_groupinfo (struct super_block*,size_t) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 struct kmem_cache* get_groupinfo_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 TYPE_1__* new_inode (struct super_block*) ; 

__attribute__((used)) static int ext4_mb_init_backend(struct super_block *sb)
{
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	ext4_group_t i;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	int err;
	struct ext4_group_desc *desc;
	struct kmem_cache *cachep;

	err = ext4_mb_alloc_groupinfo(sb, ngroups);
	if (err)
		return err;

	sbi->s_buddy_cache = new_inode(sb);
	if (sbi->s_buddy_cache == NULL) {
		ext4_msg(sb, KERN_ERR, "can't get new inode");
		goto err_freesgi;
	}
	/* To avoid potentially colliding with an valid on-disk inode number,
	 * use EXT4_BAD_INO for the buddy cache inode number.  This inode is
	 * not in the inode hash, so it should never be found by iget(), but
	 * this will avoid confusion if it ever shows up during debugging. */
	sbi->s_buddy_cache->i_ino = EXT4_BAD_INO;
	EXT4_I(sbi->s_buddy_cache)->i_disksize = 0;
	for (i = 0; i < ngroups; i++) {
		cond_resched();
		desc = ext4_get_group_desc(sb, i, NULL);
		if (desc == NULL) {
			ext4_msg(sb, KERN_ERR, "can't read descriptor %u", i);
			goto err_freebuddy;
		}
		if (ext4_mb_add_groupinfo(sb, i, desc) != 0)
			goto err_freebuddy;
	}

	return 0;

err_freebuddy:
	cachep = get_groupinfo_cache(sb->s_blocksize_bits);
	while (i-- > 0)
		kmem_cache_free(cachep, ext4_get_group_info(sb, i));
	i = sbi->s_group_info_size;
	while (i-- > 0)
		kfree(sbi->s_group_info[i]);
	iput(sbi->s_buddy_cache);
err_freesgi:
	kvfree(sbi->s_group_info);
	return -ENOMEM;
}