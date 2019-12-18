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

/* Variables and functions */
 int OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS ; 
 int OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT ; 
 int OCFS2_XATTR_INDEX_SECURITY ; 
 int ocfs2_xattr_get_type (struct ocfs2_xattr_entry*) ; 

__attribute__((used)) static int ocfs2_reflink_xattr_no_security(struct ocfs2_xattr_entry *xe)
{
	int type = ocfs2_xattr_get_type(xe);

	return type != OCFS2_XATTR_INDEX_SECURITY &&
	       type != OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS &&
	       type != OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT;
}