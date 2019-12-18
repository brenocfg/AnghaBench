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
typedef  scalar_t__ u32 ;
struct ocfs2_xattr_header {TYPE_1__* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ xe_name_hash; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ bucket_blkno (struct ocfs2_xattr_bucket*) ; 
 struct ocfs2_xattr_header* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__) ; 
 scalar_t__ ocfs2_xattr_name_hash (struct inode*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int ocfs2_check_xattr_bucket_collision(struct inode *inode,
					      struct ocfs2_xattr_bucket *bucket,
					      const char *name)
{
	struct ocfs2_xattr_header *xh = bucket_xh(bucket);
	u32 name_hash = ocfs2_xattr_name_hash(inode, name, strlen(name));

	if (name_hash != le32_to_cpu(xh->xh_entries[0].xe_name_hash))
		return 0;

	if (xh->xh_entries[le16_to_cpu(xh->xh_count) - 1].xe_name_hash ==
	    xh->xh_entries[0].xe_name_hash) {
		mlog(ML_ERROR, "Too much hash collision in xattr bucket %llu, "
		     "hash = %u\n",
		     (unsigned long long)bucket_blkno(bucket),
		     le32_to_cpu(xh->xh_entries[0].xe_name_hash));
		return -ENOSPC;
	}

	return 0;
}