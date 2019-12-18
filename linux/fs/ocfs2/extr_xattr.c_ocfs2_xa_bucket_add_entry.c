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
typedef  scalar_t__ u32 ;
struct ocfs2_xattr_header {struct ocfs2_xattr_entry* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_hash; } ;
struct ocfs2_xa_loc {struct ocfs2_xattr_entry* xl_entry; struct ocfs2_xattr_header* xl_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct ocfs2_xattr_entry*,struct ocfs2_xattr_entry*,int) ; 
 int /*<<< orphan*/  memset (struct ocfs2_xattr_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_xa_bucket_add_entry(struct ocfs2_xa_loc *loc, u32 name_hash)
{
	struct ocfs2_xattr_header *xh = loc->xl_header;
	int count = le16_to_cpu(xh->xh_count);
	int low = 0, high = count - 1, tmp;
	struct ocfs2_xattr_entry *tmp_xe;

	/*
	 * We keep buckets sorted by name_hash, so we need to find
	 * our insert place.
	 */
	while (low <= high && count) {
		tmp = (low + high) / 2;
		tmp_xe = &xh->xh_entries[tmp];

		if (name_hash > le32_to_cpu(tmp_xe->xe_name_hash))
			low = tmp + 1;
		else if (name_hash < le32_to_cpu(tmp_xe->xe_name_hash))
			high = tmp - 1;
		else {
			low = tmp;
			break;
		}
	}

	if (low != count)
		memmove(&xh->xh_entries[low + 1],
			&xh->xh_entries[low],
			((count - low) * sizeof(struct ocfs2_xattr_entry)));

	le16_add_cpu(&xh->xh_count, 1);
	loc->xl_entry = &xh->xh_entries[low];
	memset(loc->xl_entry, 0, sizeof(struct ocfs2_xattr_entry));
}