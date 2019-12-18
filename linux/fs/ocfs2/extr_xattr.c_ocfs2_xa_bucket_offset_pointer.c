#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_xa_loc {TYPE_2__* xl_inode; struct ocfs2_xattr_bucket* xl_storage; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int s_blocksize_bits; int s_blocksize; } ;

/* Variables and functions */
 void* bucket_block (struct ocfs2_xattr_bucket*,int) ; 

__attribute__((used)) static void *ocfs2_xa_bucket_offset_pointer(struct ocfs2_xa_loc *loc,
					    int offset)
{
	struct ocfs2_xattr_bucket *bucket = loc->xl_storage;
	int block, block_offset;

	/* The header is at the front of the bucket */
	block = offset >> loc->xl_inode->i_sb->s_blocksize_bits;
	block_offset = offset % loc->xl_inode->i_sb->s_blocksize;

	return bucket_block(bucket, block) + block_offset;
}