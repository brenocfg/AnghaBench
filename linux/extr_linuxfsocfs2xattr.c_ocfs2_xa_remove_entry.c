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
struct ocfs2_xattr_header {int /*<<< orphan*/ * xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct ocfs2_xa_loc {struct ocfs2_xattr_entry* xl_entry; struct ocfs2_xattr_header* xl_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocfs2_xa_wipe_namevalue (struct ocfs2_xa_loc*) ; 

__attribute__((used)) static void ocfs2_xa_remove_entry(struct ocfs2_xa_loc *loc)
{
	int index, count;
	struct ocfs2_xattr_header *xh = loc->xl_header;
	struct ocfs2_xattr_entry *entry = loc->xl_entry;

	ocfs2_xa_wipe_namevalue(loc);
	loc->xl_entry = NULL;

	le16_add_cpu(&xh->xh_count, -1);
	count = le16_to_cpu(xh->xh_count);

	/*
	 * Only zero out the entry if there are more remaining.  This is
	 * important for an empty bucket, as it keeps track of the
	 * bucket's hash value.  It doesn't hurt empty block storage.
	 */
	if (count) {
		index = ((char *)entry - (char *)&xh->xh_entries) /
			sizeof(struct ocfs2_xattr_entry);
		memmove(&xh->xh_entries[index], &xh->xh_entries[index + 1],
			(count - index) * sizeof(struct ocfs2_xattr_entry));
		memset(&xh->xh_entries[count], 0,
		       sizeof(struct ocfs2_xattr_entry));
	}
}