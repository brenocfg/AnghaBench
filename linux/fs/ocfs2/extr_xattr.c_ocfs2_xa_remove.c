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
struct ocfs2_xattr_set_ctxt {int dummy; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_xa_cleanup_value_truncate (struct ocfs2_xa_loc*,char*,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_xa_remove_entry (struct ocfs2_xa_loc*) ; 
 unsigned int ocfs2_xa_value_clusters (struct ocfs2_xa_loc*) ; 
 int ocfs2_xa_value_truncate (struct ocfs2_xa_loc*,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_xattr_is_local (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xa_remove(struct ocfs2_xa_loc *loc,
			   struct ocfs2_xattr_set_ctxt *ctxt)
{
	int rc = 0;
	unsigned int orig_clusters;

	if (!ocfs2_xattr_is_local(loc->xl_entry)) {
		orig_clusters = ocfs2_xa_value_clusters(loc);
		rc = ocfs2_xa_value_truncate(loc, 0, ctxt);
		if (rc) {
			mlog_errno(rc);
			/*
			 * Since this is remove, we can return 0 if
			 * ocfs2_xa_cleanup_value_truncate() is going to
			 * wipe the entry anyway.  So we check the
			 * cluster count as well.
			 */
			if (orig_clusters != ocfs2_xa_value_clusters(loc))
				rc = 0;
			ocfs2_xa_cleanup_value_truncate(loc, "removing",
							orig_clusters);
			if (rc)
				goto out;
		}
	}

	ocfs2_xa_remove_entry(loc);

out:
	return rc;
}