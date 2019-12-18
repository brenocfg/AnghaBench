#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct udf_fileident_bh {scalar_t__ sbh; scalar_t__ ebh; } ;
struct inode {void* i_mtime; void* i_ctime; TYPE_2__* i_sb; } ;
struct TYPE_6__ {scalar_t__ impUse; int /*<<< orphan*/  extLocation; void* extLength; } ;
struct fileIdentDesc {TYPE_1__ icb; } ;
struct dentry {int dummy; } ;
struct allocDescImpUse {scalar_t__ impUse; } ;
typedef  void* __le32 ;
struct TYPE_9__ {scalar_t__ i_alloc_type; int /*<<< orphan*/  i_location; } ;
struct TYPE_8__ {scalar_t__ s_lvid_bh; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 TYPE_5__* UDF_I (struct inode*) ; 
 TYPE_3__* UDF_SB (TYPE_2__*) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_lelb (int /*<<< orphan*/ ) ; 
 void* current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  lvid_get_unique_id (TYPE_2__*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct fileIdentDesc* udf_add_entry (struct inode*,struct dentry*,struct udf_fileident_bh*,struct fileIdentDesc*,int*) ; 
 int /*<<< orphan*/  udf_write_fi (struct inode*,struct fileIdentDesc*,struct fileIdentDesc*,struct udf_fileident_bh*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_link(struct dentry *old_dentry, struct inode *dir,
		    struct dentry *dentry)
{
	struct inode *inode = d_inode(old_dentry);
	struct udf_fileident_bh fibh;
	struct fileIdentDesc cfi, *fi;
	int err;

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	if (!fi) {
		return err;
	}
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(UDF_I(inode)->i_location);
	if (UDF_SB(inode->i_sb)->s_lvid_bh) {
		*(__le32 *)((struct allocDescImpUse *)cfi.icb.impUse)->impUse =
			cpu_to_le32(lvid_get_unique_id(inode->i_sb));
	}
	udf_write_fi(dir, &cfi, fi, &fibh, NULL, NULL);
	if (UDF_I(dir)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		mark_inode_dirty(dir);

	if (fibh.sbh != fibh.ebh)
		brelse(fibh.ebh);
	brelse(fibh.sbh);
	inc_nlink(inode);
	inode->i_ctime = current_time(inode);
	mark_inode_dirty(inode);
	dir->i_ctime = dir->i_mtime = current_time(dir);
	mark_inode_dirty(dir);
	ihold(inode);
	d_instantiate(dentry, inode);

	return 0;
}