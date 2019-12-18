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
struct ocfs2_xattr_entry {int dummy; } ;
struct ocfs2_xattr_bucket {int /*<<< orphan*/  bu_inode; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_size; struct ocfs2_xattr_entry* xl_entry; int /*<<< orphan*/  xl_header; struct ocfs2_xattr_bucket* xl_storage; int /*<<< orphan*/ * xl_ops; int /*<<< orphan*/  xl_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_XATTR_BUCKET_SIZE ; 
 int /*<<< orphan*/  bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  ocfs2_xa_bucket_loc_ops ; 

__attribute__((used)) static void ocfs2_init_xattr_bucket_xa_loc(struct ocfs2_xa_loc *loc,
					   struct ocfs2_xattr_bucket *bucket,
					   struct ocfs2_xattr_entry *entry)
{
	loc->xl_inode = bucket->bu_inode;
	loc->xl_ops = &ocfs2_xa_bucket_loc_ops;
	loc->xl_storage = bucket;
	loc->xl_header = bucket_xh(bucket);
	loc->xl_entry = entry;
	loc->xl_size = OCFS2_XATTR_BUCKET_SIZE;
}