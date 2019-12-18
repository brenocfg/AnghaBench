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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_dir_lookup_result {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 char* OCFS2_DIO_ORPHAN_PREFIX ; 
 int OCFS2_DIO_ORPHAN_PREFIX_LEN ; 
 int OCFS2_ORPHAN_NAMELEN ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_blkno_stringify (int /*<<< orphan*/ ,char*) ; 
 int ocfs2_prepare_dir_for_insert (struct ocfs2_super*,struct inode*,struct buffer_head*,char*,int,struct ocfs2_dir_lookup_result*) ; 
 int snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int __ocfs2_prepare_orphan_dir(struct inode *orphan_dir_inode,
				      struct buffer_head *orphan_dir_bh,
				      u64 blkno,
				      char *name,
				      struct ocfs2_dir_lookup_result *lookup,
				      bool dio)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(orphan_dir_inode->i_sb);
	int namelen = dio ?
			(OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN) :
			OCFS2_ORPHAN_NAMELEN;

	if (dio) {
		ret = snprintf(name, OCFS2_DIO_ORPHAN_PREFIX_LEN + 1, "%s",
				OCFS2_DIO_ORPHAN_PREFIX);
		if (ret != OCFS2_DIO_ORPHAN_PREFIX_LEN) {
			ret = -EINVAL;
			mlog_errno(ret);
			return ret;
		}

		ret = ocfs2_blkno_stringify(blkno,
				name + OCFS2_DIO_ORPHAN_PREFIX_LEN);
	} else
		ret = ocfs2_blkno_stringify(blkno, name);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	ret = ocfs2_prepare_dir_for_insert(osb, orphan_dir_inode,
					   orphan_dir_bh, name,
					   namelen, lookup);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	return 0;
}