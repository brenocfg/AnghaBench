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
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_inode_info {unsigned long long ip_dir_lock_gen; scalar_t__ ip_blkno; } ;
struct inode {int /*<<< orphan*/  i_mode; struct address_space* i_mapping; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int /*<<< orphan*/  ML_ERROR ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int UNBLOCK_CONTINUE ; 
 int /*<<< orphan*/  filemap_fdatawait (struct address_space*) ; 
 scalar_t__ filemap_fdatawrite (struct address_space*) ; 
 int /*<<< orphan*/  forget_all_cached_acls (struct inode*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 struct inode* ocfs2_lock_res_inode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  sync_mapping_buffers (struct address_space*) ; 
 int /*<<< orphan*/  truncate_inode_pages (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unmap_mapping_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_data_convert_worker(struct ocfs2_lock_res *lockres,
				     int blocking)
{
	struct inode *inode;
	struct address_space *mapping;
	struct ocfs2_inode_info *oi;

       	inode = ocfs2_lock_res_inode(lockres);
	mapping = inode->i_mapping;

	if (S_ISDIR(inode->i_mode)) {
		oi = OCFS2_I(inode);
		oi->ip_dir_lock_gen++;
		mlog(0, "generation: %u\n", oi->ip_dir_lock_gen);
		goto out;
	}

	if (!S_ISREG(inode->i_mode))
		goto out;

	/*
	 * We need this before the filemap_fdatawrite() so that it can
	 * transfer the dirty bit from the PTE to the
	 * page. Unfortunately this means that even for EX->PR
	 * downconverts, we'll lose our mappings and have to build
	 * them up again.
	 */
	unmap_mapping_range(mapping, 0, 0, 0);

	if (filemap_fdatawrite(mapping)) {
		mlog(ML_ERROR, "Could not sync inode %llu for downconvert!",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
	}
	sync_mapping_buffers(mapping);
	if (blocking == DLM_LOCK_EX) {
		truncate_inode_pages(mapping, 0);
	} else {
		/* We only need to wait on the I/O if we're not also
		 * truncating pages because truncate_inode_pages waits
		 * for us above. We don't truncate pages if we're
		 * blocking anything < EXMODE because we want to keep
		 * them around in that case. */
		filemap_fdatawait(mapping);
	}

	forget_all_cached_acls(inode);

out:
	return UNBLOCK_CONTINUE;
}