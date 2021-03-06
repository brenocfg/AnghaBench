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
struct ocfs2_xattr_bucket {int dummy; } ;
struct ocfs2_xa_loc {struct ocfs2_xattr_bucket* xl_storage; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ocfs2_xattr_bucket_journal_access (int /*<<< orphan*/ *,struct ocfs2_xattr_bucket*,int) ; 

__attribute__((used)) static int ocfs2_xa_bucket_journal_access(handle_t *handle,
					  struct ocfs2_xa_loc *loc, int type)
{
	struct ocfs2_xattr_bucket *bucket = loc->xl_storage;

	return ocfs2_xattr_bucket_journal_access(handle, bucket, type);
}