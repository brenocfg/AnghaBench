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
typedef  scalar_t__ u64 ;
typedef  size_t u16 ;
struct ocfs2_xattr_header {void* xh_count; void* xh_free_start; struct ocfs2_xattr_entry* xh_entries; void* xh_name_value_len; } ;
struct ocfs2_xattr_entry {void* xe_name_offset; } ;
struct ocfs2_xattr_bucket {int bu_blocks; } ;
struct inode {TYPE_1__* i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {size_t s_blocksize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 size_t OCFS2_XATTR_BUCKET_SIZE ; 
 scalar_t__ bucket_blkno (struct ocfs2_xattr_bucket*) ; 
 char* bucket_block (struct ocfs2_xattr_bucket*,int) ; 
 int /*<<< orphan*/  cmp_xe ; 
 int /*<<< orphan*/  cmp_xe_offset ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 size_t namevalue_size_xe (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_journal_dirty (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  sort (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_xe ; 
 int /*<<< orphan*/  trace_ocfs2_defrag_xattr_bucket (unsigned long long,int,size_t,int) ; 

__attribute__((used)) static int ocfs2_defrag_xattr_bucket(struct inode *inode,
				     handle_t *handle,
				     struct ocfs2_xattr_bucket *bucket)
{
	int ret, i;
	size_t end, offset, len;
	struct ocfs2_xattr_header *xh;
	char *entries, *buf, *bucket_buf = NULL;
	u64 blkno = bucket_blkno(bucket);
	u16 xh_free_start;
	size_t blocksize = inode->i_sb->s_blocksize;
	struct ocfs2_xattr_entry *xe;

	/*
	 * In order to make the operation more efficient and generic,
	 * we copy all the blocks into a contiguous memory and do the
	 * defragment there, so if anything is error, we will not touch
	 * the real block.
	 */
	bucket_buf = kmalloc(OCFS2_XATTR_BUCKET_SIZE, GFP_NOFS);
	if (!bucket_buf) {
		ret = -EIO;
		goto out;
	}

	buf = bucket_buf;
	for (i = 0; i < bucket->bu_blocks; i++, buf += blocksize)
		memcpy(buf, bucket_block(bucket, i), blocksize);

	ret = ocfs2_xattr_bucket_journal_access(handle, bucket,
						OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}

	xh = (struct ocfs2_xattr_header *)bucket_buf;
	entries = (char *)xh->xh_entries;
	xh_free_start = le16_to_cpu(xh->xh_free_start);

	trace_ocfs2_defrag_xattr_bucket(
	     (unsigned long long)blkno, le16_to_cpu(xh->xh_count),
	     xh_free_start, le16_to_cpu(xh->xh_name_value_len));

	/*
	 * sort all the entries by their offset.
	 * the largest will be the first, so that we can
	 * move them to the end one by one.
	 */
	sort(entries, le16_to_cpu(xh->xh_count),
	     sizeof(struct ocfs2_xattr_entry),
	     cmp_xe_offset, swap_xe);

	/* Move all name/values to the end of the bucket. */
	xe = xh->xh_entries;
	end = OCFS2_XATTR_BUCKET_SIZE;
	for (i = 0; i < le16_to_cpu(xh->xh_count); i++, xe++) {
		offset = le16_to_cpu(xe->xe_name_offset);
		len = namevalue_size_xe(xe);

		/*
		 * We must make sure that the name/value pair
		 * exist in the same block. So adjust end to
		 * the previous block end if needed.
		 */
		if (((end - len) / blocksize !=
			(end - 1) / blocksize))
			end = end - end % blocksize;

		if (end > offset + len) {
			memmove(bucket_buf + end - len,
				bucket_buf + offset, len);
			xe->xe_name_offset = cpu_to_le16(end - len);
		}

		mlog_bug_on_msg(end < offset + len, "Defrag check failed for "
				"bucket %llu\n", (unsigned long long)blkno);

		end -= len;
	}

	mlog_bug_on_msg(xh_free_start > end, "Defrag check failed for "
			"bucket %llu\n", (unsigned long long)blkno);

	if (xh_free_start == end)
		goto out;

	memset(bucket_buf + xh_free_start, 0, end - xh_free_start);
	xh->xh_free_start = cpu_to_le16(end);

	/* sort the entries by their name_hash. */
	sort(entries, le16_to_cpu(xh->xh_count),
	     sizeof(struct ocfs2_xattr_entry),
	     cmp_xe, swap_xe);

	buf = bucket_buf;
	for (i = 0; i < bucket->bu_blocks; i++, buf += blocksize)
		memcpy(bucket_block(bucket, i), buf, blocksize);
	ocfs2_xattr_bucket_journal_dirty(handle, bucket);

out:
	kfree(bucket_buf);
	return ret;
}