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
struct ocfs2_xattr_bucket {int /*<<< orphan*/ * bu_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (struct ocfs2_xattr_bucket*) ; 

__attribute__((used)) static void ocfs2_xattr_bucket_free(struct ocfs2_xattr_bucket *bucket)
{
	if (bucket) {
		ocfs2_xattr_bucket_relse(bucket);
		bucket->bu_inode = NULL;
		kfree(bucket);
	}
}