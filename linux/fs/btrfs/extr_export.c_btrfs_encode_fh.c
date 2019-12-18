#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int /*<<< orphan*/  i_generation; } ;
struct btrfs_fid {scalar_t__ root_objectid; scalar_t__ parent_root_objectid; int /*<<< orphan*/  parent_gen; int /*<<< orphan*/  parent_objectid; int /*<<< orphan*/  gen; int /*<<< orphan*/  objectid; } ;
struct TYPE_6__ {int /*<<< orphan*/  objectid; } ;
struct TYPE_9__ {TYPE_3__* root; TYPE_1__ location; } ;
struct TYPE_7__ {scalar_t__ objectid; } ;
struct TYPE_8__ {TYPE_2__ root_key; } ;

/* Variables and functions */
 int BTRFS_FID_SIZE_CONNECTABLE ; 
 int BTRFS_FID_SIZE_CONNECTABLE_ROOT ; 
 int BTRFS_FID_SIZE_NON_CONNECTABLE ; 
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int FILEID_BTRFS_WITHOUT_PARENT ; 
 int FILEID_BTRFS_WITH_PARENT ; 
 int FILEID_BTRFS_WITH_PARENT_ROOT ; 
 int FILEID_INVALID ; 
 int /*<<< orphan*/  btrfs_ino (TYPE_4__*) ; 

__attribute__((used)) static int btrfs_encode_fh(struct inode *inode, u32 *fh, int *max_len,
			   struct inode *parent)
{
	struct btrfs_fid *fid = (struct btrfs_fid *)fh;
	int len = *max_len;
	int type;

	if (parent && (len < BTRFS_FID_SIZE_CONNECTABLE)) {
		*max_len = BTRFS_FID_SIZE_CONNECTABLE;
		return FILEID_INVALID;
	} else if (len < BTRFS_FID_SIZE_NON_CONNECTABLE) {
		*max_len = BTRFS_FID_SIZE_NON_CONNECTABLE;
		return FILEID_INVALID;
	}

	len  = BTRFS_FID_SIZE_NON_CONNECTABLE;
	type = FILEID_BTRFS_WITHOUT_PARENT;

	fid->objectid = btrfs_ino(BTRFS_I(inode));
	fid->root_objectid = BTRFS_I(inode)->root->root_key.objectid;
	fid->gen = inode->i_generation;

	if (parent) {
		u64 parent_root_id;

		fid->parent_objectid = BTRFS_I(parent)->location.objectid;
		fid->parent_gen = parent->i_generation;
		parent_root_id = BTRFS_I(parent)->root->root_key.objectid;

		if (parent_root_id != fid->root_objectid) {
			fid->parent_root_objectid = parent_root_id;
			len = BTRFS_FID_SIZE_CONNECTABLE_ROOT;
			type = FILEID_BTRFS_WITH_PARENT_ROOT;
		} else {
			len = BTRFS_FID_SIZE_CONNECTABLE;
			type = FILEID_BTRFS_WITH_PARENT;
		}
	}

	*max_len = len;
	return type;
}