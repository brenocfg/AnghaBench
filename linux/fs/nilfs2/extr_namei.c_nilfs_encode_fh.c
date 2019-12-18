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
struct nilfs_root {int /*<<< orphan*/  cno; } ;
struct nilfs_fid {int /*<<< orphan*/  parent_gen; int /*<<< orphan*/  parent_ino; int /*<<< orphan*/  gen; int /*<<< orphan*/  ino; int /*<<< orphan*/  cno; } ;
struct inode {int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_ino; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {struct nilfs_root* i_root; } ;

/* Variables and functions */
 int FILEID_INVALID ; 
 int FILEID_NILFS_WITHOUT_PARENT ; 
 int FILEID_NILFS_WITH_PARENT ; 
 int NILFS_FID_SIZE_CONNECTABLE ; 
 int NILFS_FID_SIZE_NON_CONNECTABLE ; 
 TYPE_1__* NILFS_I (struct inode*) ; 

__attribute__((used)) static int nilfs_encode_fh(struct inode *inode, __u32 *fh, int *lenp,
			   struct inode *parent)
{
	struct nilfs_fid *fid = (struct nilfs_fid *)fh;
	struct nilfs_root *root = NILFS_I(inode)->i_root;
	int type;

	if (parent && *lenp < NILFS_FID_SIZE_CONNECTABLE) {
		*lenp = NILFS_FID_SIZE_CONNECTABLE;
		return FILEID_INVALID;
	}
	if (*lenp < NILFS_FID_SIZE_NON_CONNECTABLE) {
		*lenp = NILFS_FID_SIZE_NON_CONNECTABLE;
		return FILEID_INVALID;
	}

	fid->cno = root->cno;
	fid->ino = inode->i_ino;
	fid->gen = inode->i_generation;

	if (parent) {
		fid->parent_ino = parent->i_ino;
		fid->parent_gen = parent->i_generation;
		type = FILEID_NILFS_WITH_PARENT;
		*lenp = NILFS_FID_SIZE_CONNECTABLE;
	} else {
		type = FILEID_NILFS_WITHOUT_PARENT;
		*lenp = NILFS_FID_SIZE_NON_CONNECTABLE;
	}

	return type;
}