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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {TYPE_1__* zbranch; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_mode; } ;
typedef  int loff_t ;
struct TYPE_2__ {union ubifs_key key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int UBIFS_BLOCK_SHIFT ; 
 int /*<<< orphan*/  UBIFS_BLOCK_SIZE ; 
 int /*<<< orphan*/  data_key_init (struct ubifs_info*,union ubifs_key*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dbg_is_chk_gen (struct ubifs_info*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  highest_data_key (struct ubifs_info*,union ubifs_key*,scalar_t__) ; 
 unsigned int key_block (struct ubifs_info*,union ubifs_key*) ; 
 int /*<<< orphan*/  key_in_range (struct ubifs_info*,union ubifs_key*,union ubifs_key*,union ubifs_key*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tnc_next (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  ubifs_assert (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  ubifs_dump_inode (struct ubifs_info*,struct inode const*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,unsigned long,int,int) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 

int dbg_check_inode_size(struct ubifs_info *c, const struct inode *inode,
			 loff_t size)
{
	int err, n;
	union ubifs_key from_key, to_key, *key;
	struct ubifs_znode *znode;
	unsigned int block;

	if (!S_ISREG(inode->i_mode))
		return 0;
	if (!dbg_is_chk_gen(c))
		return 0;

	block = (size + UBIFS_BLOCK_SIZE - 1) >> UBIFS_BLOCK_SHIFT;
	data_key_init(c, &from_key, inode->i_ino, block);
	highest_data_key(c, &to_key, inode->i_ino);

	mutex_lock(&c->tnc_mutex);
	err = ubifs_lookup_level0(c, &from_key, &znode, &n);
	if (err < 0)
		goto out_unlock;

	if (err) {
		key = &from_key;
		goto out_dump;
	}

	err = tnc_next(c, &znode, &n);
	if (err == -ENOENT) {
		err = 0;
		goto out_unlock;
	}
	if (err < 0)
		goto out_unlock;

	ubifs_assert(c, err == 0);
	key = &znode->zbranch[n].key;
	if (!key_in_range(c, key, &from_key, &to_key))
		goto out_unlock;

out_dump:
	block = key_block(c, key);
	ubifs_err(c, "inode %lu has size %lld, but there are data at offset %lld",
		  (unsigned long)inode->i_ino, size,
		  ((loff_t)block) << UBIFS_BLOCK_SHIFT);
	mutex_unlock(&c->tnc_mutex);
	ubifs_dump_inode(c, inode);
	dump_stack();
	return -EINVAL;

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}