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
struct ocfs2_xa_loc {TYPE_1__* xl_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 
 char* ocfs2_xa_offset_pointer (struct ocfs2_xa_loc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xa_remove_entry (struct ocfs2_xa_loc*) ; 
 unsigned int ocfs2_xa_value_clusters (struct ocfs2_xa_loc*) ; 

__attribute__((used)) static void ocfs2_xa_cleanup_value_truncate(struct ocfs2_xa_loc *loc,
					    const char *what,
					    unsigned int orig_clusters)
{
	unsigned int new_clusters = ocfs2_xa_value_clusters(loc);
	char *nameval_buf = ocfs2_xa_offset_pointer(loc,
				le16_to_cpu(loc->xl_entry->xe_name_offset));

	if (new_clusters < orig_clusters) {
		mlog(ML_ERROR,
		     "Partial truncate while %s xattr %.*s.  Leaking "
		     "%u clusters and removing the entry\n",
		     what, loc->xl_entry->xe_name_len, nameval_buf,
		     orig_clusters - new_clusters);
		ocfs2_xa_remove_entry(loc);
	} else if (!orig_clusters) {
		mlog(ML_ERROR,
		     "Unable to allocate an external value for xattr "
		     "%.*s safely.  Leaking %u clusters and removing the "
		     "entry\n",
		     loc->xl_entry->xe_name_len, nameval_buf,
		     new_clusters - orig_clusters);
		ocfs2_xa_remove_entry(loc);
	} else if (new_clusters > orig_clusters)
		mlog(ML_ERROR,
		     "Unable to grow xattr %.*s safely.  %u new clusters "
		     "have been added, but the value will not be "
		     "modified\n",
		     loc->xl_entry->xe_name_len, nameval_buf,
		     new_clusters - orig_clusters);
}