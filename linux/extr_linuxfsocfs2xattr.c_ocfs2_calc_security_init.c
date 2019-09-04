#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int dummy; } ;
struct ocfs2_security_xattr_info {scalar_t__ value_len; int /*<<< orphan*/  name; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_4__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ OCFS2_MIN_BLOCKSIZE ; 
 struct ocfs2_super* OCFS2_SB (TYPE_1__*) ; 
 scalar_t__ OCFS2_XATTR_BLOCK_CREATE_CREDITS ; 
 int OCFS2_XATTR_FREE_IN_IBODY ; 
 scalar_t__ OCFS2_XATTR_INLINE_SIZE ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_clusters_for_bytes (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (TYPE_1__*,int) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_xattr_entry_real_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

int ocfs2_calc_security_init(struct inode *dir,
			     struct ocfs2_security_xattr_info *si,
			     int *want_clusters,
			     int *xattr_credits,
			     struct ocfs2_alloc_context **xattr_ac)
{
	int ret = 0;
	struct ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	int s_size = ocfs2_xattr_entry_real_size(strlen(si->name),
						 si->value_len);

	/*
	 * The max space of security xattr taken inline is
	 * 256(name) + 80(value) + 16(entry) = 352 bytes,
	 * So reserve one metadata block for it is ok.
	 */
	if (dir->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE ||
	    s_size > OCFS2_XATTR_FREE_IN_IBODY) {
		ret = ocfs2_reserve_new_metadata_blocks(osb, 1, xattr_ac);
		if (ret) {
			mlog_errno(ret);
			return ret;
		}
		*xattr_credits += OCFS2_XATTR_BLOCK_CREATE_CREDITS;
	}

	/* reserve clusters for xattr value which will be set in B tree*/
	if (si->value_len > OCFS2_XATTR_INLINE_SIZE) {
		int new_clusters = ocfs2_clusters_for_bytes(dir->i_sb,
							    si->value_len);

		*xattr_credits += ocfs2_clusters_to_blocks(dir->i_sb,
							   new_clusters);
		*want_clusters += new_clusters;
	}
	return ret;
}