#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct CodaFid {int dummy; } ;
struct TYPE_8__ {struct CodaFid NewFid; struct CodaFid OldFid; } ;
struct TYPE_7__ {struct CodaFid CodaFid; } ;
struct TYPE_6__ {struct CodaFid CodaFid; } ;
struct TYPE_5__ {struct CodaFid CodaFid; } ;
union outputArgs {TYPE_4__ coda_replace; TYPE_3__ coda_purgefid; TYPE_2__ coda_zapfile; TYPE_1__ coda_zapdir; } ;
struct venus_comm {int /*<<< orphan*/  vc_mutex; struct super_block* vc_sb; } ;
struct super_block {int /*<<< orphan*/  s_root; } ;
struct inode {int dummy; } ;
struct coda_zapfile_out {int dummy; } ;
struct coda_zapdir_out {int dummy; } ;
struct coda_replace_out {int dummy; } ;
struct coda_purgeuser_out {int dummy; } ;
struct coda_purgefid_out {int dummy; } ;

/* Variables and functions */
#define  CODA_FLUSH 133 
#define  CODA_PURGEFID 132 
#define  CODA_PURGEUSER 131 
#define  CODA_REPLACE 130 
#define  CODA_ZAPDIR 129 
#define  CODA_ZAPFILE 128 
 int /*<<< orphan*/  C_FLUSH ; 
 int /*<<< orphan*/  C_PURGE ; 
 int /*<<< orphan*/  C_VATTR ; 
 int EINVAL ; 
 int /*<<< orphan*/  coda_cache_clear_all (struct super_block*) ; 
 struct inode* coda_fid_to_inode (struct CodaFid*,struct super_block*) ; 
 int /*<<< orphan*/  coda_flag_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_flag_inode_children (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_replace_fid (struct inode*,struct CodaFid*,struct CodaFid*) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_prune_aliases (struct inode*) ; 
 int /*<<< orphan*/  d_really_is_positive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shrink_dcache_sb (struct super_block*) ; 

int coda_downcall(struct venus_comm *vcp, int opcode, union outputArgs *out,
		  size_t nbytes)
{
	struct inode *inode = NULL;
	struct CodaFid *fid = NULL, *newfid;
	struct super_block *sb;

	/*
	 * Make sure we have received enough data from the cache
	 * manager to populate the necessary fields in the buffer
	 */
	switch (opcode) {
	case CODA_PURGEUSER:
		if (nbytes < sizeof(struct coda_purgeuser_out))
			return -EINVAL;
		break;

	case CODA_ZAPDIR:
		if (nbytes < sizeof(struct coda_zapdir_out))
			return -EINVAL;
		break;

	case CODA_ZAPFILE:
		if (nbytes < sizeof(struct coda_zapfile_out))
			return -EINVAL;
		break;

	case CODA_PURGEFID:
		if (nbytes < sizeof(struct coda_purgefid_out))
			return -EINVAL;
		break;

	case CODA_REPLACE:
		if (nbytes < sizeof(struct coda_replace_out))
			return -EINVAL;
		break;
	}

	/* Handle invalidation requests. */
	mutex_lock(&vcp->vc_mutex);
	sb = vcp->vc_sb;
	if (!sb || !sb->s_root)
		goto unlock_out;

	switch (opcode) {
	case CODA_FLUSH:
		coda_cache_clear_all(sb);
		shrink_dcache_sb(sb);
		if (d_really_is_positive(sb->s_root))
			coda_flag_inode(d_inode(sb->s_root), C_FLUSH);
		break;

	case CODA_PURGEUSER:
		coda_cache_clear_all(sb);
		break;

	case CODA_ZAPDIR:
		fid = &out->coda_zapdir.CodaFid;
		break;

	case CODA_ZAPFILE:
		fid = &out->coda_zapfile.CodaFid;
		break;

	case CODA_PURGEFID:
		fid = &out->coda_purgefid.CodaFid;
		break;

	case CODA_REPLACE:
		fid = &out->coda_replace.OldFid;
		break;
	}
	if (fid)
		inode = coda_fid_to_inode(fid, sb);

unlock_out:
	mutex_unlock(&vcp->vc_mutex);

	if (!inode)
		return 0;

	switch (opcode) {
	case CODA_ZAPDIR:
		coda_flag_inode_children(inode, C_PURGE);
		coda_flag_inode(inode, C_VATTR);
		break;

	case CODA_ZAPFILE:
		coda_flag_inode(inode, C_VATTR);
		break;

	case CODA_PURGEFID:
		coda_flag_inode_children(inode, C_PURGE);

		/* catch the dentries later if some are still busy */
		coda_flag_inode(inode, C_PURGE);
		d_prune_aliases(inode);
		break;

	case CODA_REPLACE:
		newfid = &out->coda_replace.NewFid;
		coda_replace_fid(inode, fid, newfid);
		break;
	}
	iput(inode);
	return 0;
}