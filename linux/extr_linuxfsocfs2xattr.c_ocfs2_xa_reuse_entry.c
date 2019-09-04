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
struct ocfs2_xattr_set_ctxt {int dummy; } ;
struct ocfs2_xattr_info {scalar_t__ xi_value_len; int /*<<< orphan*/  xi_name_len; } ;
struct ocfs2_xa_loc {TYPE_1__* xl_entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  xe_value_size; int /*<<< orphan*/  xe_name_offset; int /*<<< orphan*/  xe_name_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_XATTR_INLINE_SIZE ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ namevalue_size_xe (TYPE_1__*) ; 
 int /*<<< orphan*/  ocfs2_xa_cleanup_value_truncate (struct ocfs2_xa_loc*,char*,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_xa_install_value_root (struct ocfs2_xa_loc*) ; 
 char* ocfs2_xa_offset_pointer (struct ocfs2_xa_loc*,int /*<<< orphan*/ ) ; 
 unsigned int ocfs2_xa_value_clusters (struct ocfs2_xa_loc*) ; 
 int ocfs2_xa_value_truncate (struct ocfs2_xa_loc*,scalar_t__,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_xattr_is_local (TYPE_1__*) ; 
 int /*<<< orphan*/  ocfs2_xattr_set_local (TYPE_1__*,int) ; 

__attribute__((used)) static int ocfs2_xa_reuse_entry(struct ocfs2_xa_loc *loc,
				struct ocfs2_xattr_info *xi,
				struct ocfs2_xattr_set_ctxt *ctxt)
{
	int rc = 0;
	int name_size = OCFS2_XATTR_SIZE(xi->xi_name_len);
	unsigned int orig_clusters;
	char *nameval_buf;
	int xe_local = ocfs2_xattr_is_local(loc->xl_entry);
	int xi_local = xi->xi_value_len <= OCFS2_XATTR_INLINE_SIZE;

	BUG_ON(OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len) !=
	       name_size);

	nameval_buf = ocfs2_xa_offset_pointer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));
	if (xe_local) {
		memset(nameval_buf + name_size, 0,
		       namevalue_size_xe(loc->xl_entry) - name_size);
		if (!xi_local)
			ocfs2_xa_install_value_root(loc);
	} else {
		orig_clusters = ocfs2_xa_value_clusters(loc);
		if (xi_local) {
			rc = ocfs2_xa_value_truncate(loc, 0, ctxt);
			if (rc < 0)
				mlog_errno(rc);
			else
				memset(nameval_buf + name_size, 0,
				       namevalue_size_xe(loc->xl_entry) -
				       name_size);
		} else if (le64_to_cpu(loc->xl_entry->xe_value_size) >
			   xi->xi_value_len) {
			rc = ocfs2_xa_value_truncate(loc, xi->xi_value_len,
						     ctxt);
			if (rc < 0)
				mlog_errno(rc);
		}

		if (rc) {
			ocfs2_xa_cleanup_value_truncate(loc, "reusing",
							orig_clusters);
			goto out;
		}
	}

	loc->xl_entry->xe_value_size = cpu_to_le64(xi->xi_value_len);
	ocfs2_xattr_set_local(loc->xl_entry, xi_local);

out:
	return rc;
}