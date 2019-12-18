#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {scalar_t__ objectid; } ;
struct btrfs_root {TYPE_1__ root_key; } ;
struct btrfs_fs_info {int dummy; } ;
struct bio {scalar_t__ bi_status; } ;
typedef  enum btrfs_wq_endio_type { ____Placeholder_btrfs_wq_endio_type } btrfs_wq_endio_type ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  sync_writers; struct btrfs_root* root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_DATA_RELOC_TREE_OBJECTID ; 
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 int BTRFS_WQ_ENDIO_DATA ; 
 int BTRFS_WQ_ENDIO_FREE_SPACE ; 
 unsigned long EXTENT_BIO_COMPRESSED ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ btrfs_bio_wq_end_io (struct btrfs_fs_info*,struct bio*,int) ; 
 scalar_t__ btrfs_csum_one_bio (struct inode*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_is_free_space_inode (TYPE_2__*) ; 
 scalar_t__ btrfs_lookup_bio_sums (struct inode*,struct bio*,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_map_bio (struct btrfs_fs_info*,struct bio*,int,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_submit_bio_start ; 
 scalar_t__ btrfs_submit_compressed_read (struct inode*,struct bio*,int,unsigned long) ; 
 scalar_t__ btrfs_wq_submit_bio (struct btrfs_fs_info*,struct bio*,int,unsigned long,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t btrfs_submit_bio_hook(struct inode *inode, struct bio *bio,
					  int mirror_num,
					  unsigned long bio_flags)

{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	enum btrfs_wq_endio_type metadata = BTRFS_WQ_ENDIO_DATA;
	blk_status_t ret = 0;
	int skip_sum;
	int async = !atomic_read(&BTRFS_I(inode)->sync_writers);

	skip_sum = BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM;

	if (btrfs_is_free_space_inode(BTRFS_I(inode)))
		metadata = BTRFS_WQ_ENDIO_FREE_SPACE;

	if (bio_op(bio) != REQ_OP_WRITE) {
		ret = btrfs_bio_wq_end_io(fs_info, bio, metadata);
		if (ret)
			goto out;

		if (bio_flags & EXTENT_BIO_COMPRESSED) {
			ret = btrfs_submit_compressed_read(inode, bio,
							   mirror_num,
							   bio_flags);
			goto out;
		} else if (!skip_sum) {
			ret = btrfs_lookup_bio_sums(inode, bio, NULL);
			if (ret)
				goto out;
		}
		goto mapit;
	} else if (async && !skip_sum) {
		/* csum items have already been cloned */
		if (root->root_key.objectid == BTRFS_DATA_RELOC_TREE_OBJECTID)
			goto mapit;
		/* we're doing a write, do the async checksumming */
		ret = btrfs_wq_submit_bio(fs_info, bio, mirror_num, bio_flags,
					  0, inode, btrfs_submit_bio_start);
		goto out;
	} else if (!skip_sum) {
		ret = btrfs_csum_one_bio(inode, bio, 0, 0);
		if (ret)
			goto out;
	}

mapit:
	ret = btrfs_map_bio(fs_info, bio, mirror_num, 0);

out:
	if (ret) {
		bio->bi_status = ret;
		bio_endio(bio);
	}
	return ret;
}