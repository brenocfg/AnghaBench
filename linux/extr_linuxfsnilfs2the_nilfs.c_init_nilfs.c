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
struct the_nilfs {int ns_blocksize; int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_mount_state; int /*<<< orphan*/  ns_next_generation; int /*<<< orphan*/  ns_blocksize_bits; } ;
struct super_block {int s_blocksize; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/  s_bdev; } ;
struct nilfs_super_block {int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_log_block_size; } ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int NILFS_MAX_BLOCK_SIZE ; 
 int NILFS_MIN_BLOCK_SIZE ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int nilfs_check_feature_compatibility (struct super_block*,struct nilfs_super_block*) ; 
 int nilfs_load_super_block (struct the_nilfs*,struct super_block*,int,struct nilfs_super_block**) ; 
 int /*<<< orphan*/  nilfs_max_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nilfs_release_super_block (struct the_nilfs*) ; 
 int nilfs_store_disk_layout (struct the_nilfs*,struct nilfs_super_block*) ; 
 int nilfs_store_log_cursor (struct the_nilfs*,struct nilfs_super_block*) ; 
 int nilfs_store_magic_and_option (struct super_block*,struct nilfs_super_block*,char*) ; 
 int nilfs_sysfs_create_device_group (struct super_block*) ; 
 int sb_min_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int) ; 
 int /*<<< orphan*/  set_nilfs_init (struct the_nilfs*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int init_nilfs(struct the_nilfs *nilfs, struct super_block *sb, char *data)
{
	struct nilfs_super_block *sbp;
	int blocksize;
	int err;

	down_write(&nilfs->ns_sem);

	blocksize = sb_min_blocksize(sb, NILFS_MIN_BLOCK_SIZE);
	if (!blocksize) {
		nilfs_msg(sb, KERN_ERR, "unable to set blocksize");
		err = -EINVAL;
		goto out;
	}
	err = nilfs_load_super_block(nilfs, sb, blocksize, &sbp);
	if (err)
		goto out;

	err = nilfs_store_magic_and_option(sb, sbp, data);
	if (err)
		goto failed_sbh;

	err = nilfs_check_feature_compatibility(sb, sbp);
	if (err)
		goto failed_sbh;

	blocksize = BLOCK_SIZE << le32_to_cpu(sbp->s_log_block_size);
	if (blocksize < NILFS_MIN_BLOCK_SIZE ||
	    blocksize > NILFS_MAX_BLOCK_SIZE) {
		nilfs_msg(sb, KERN_ERR,
			  "couldn't mount because of unsupported filesystem blocksize %d",
			  blocksize);
		err = -EINVAL;
		goto failed_sbh;
	}
	if (sb->s_blocksize != blocksize) {
		int hw_blocksize = bdev_logical_block_size(sb->s_bdev);

		if (blocksize < hw_blocksize) {
			nilfs_msg(sb, KERN_ERR,
				  "blocksize %d too small for device (sector-size = %d)",
				  blocksize, hw_blocksize);
			err = -EINVAL;
			goto failed_sbh;
		}
		nilfs_release_super_block(nilfs);
		sb_set_blocksize(sb, blocksize);

		err = nilfs_load_super_block(nilfs, sb, blocksize, &sbp);
		if (err)
			goto out;
			/*
			 * Not to failed_sbh; sbh is released automatically
			 * when reloading fails.
			 */
	}
	nilfs->ns_blocksize_bits = sb->s_blocksize_bits;
	nilfs->ns_blocksize = blocksize;

	get_random_bytes(&nilfs->ns_next_generation,
			 sizeof(nilfs->ns_next_generation));

	err = nilfs_store_disk_layout(nilfs, sbp);
	if (err)
		goto failed_sbh;

	sb->s_maxbytes = nilfs_max_size(sb->s_blocksize_bits);

	nilfs->ns_mount_state = le16_to_cpu(sbp->s_state);

	err = nilfs_store_log_cursor(nilfs, sbp);
	if (err)
		goto failed_sbh;

	err = nilfs_sysfs_create_device_group(sb);
	if (err)
		goto failed_sbh;

	set_nilfs_init(nilfs);
	err = 0;
 out:
	up_write(&nilfs->ns_sem);
	return err;

 failed_sbh:
	nilfs_release_super_block(nilfs);
	goto out;
}