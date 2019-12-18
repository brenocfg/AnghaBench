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
struct ocfs2_xattr_header {TYPE_1__* xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_xattr_entry {int /*<<< orphan*/  xe_name_offset; } ;
struct ocfs2_xa_loc {struct ocfs2_xattr_header* xl_header; struct ocfs2_xattr_entry* xl_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  xe_name_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int namevalue_size_xe (struct ocfs2_xattr_entry*) ; 
 int ocfs2_xa_get_free_start (struct ocfs2_xa_loc*) ; 

__attribute__((used)) static void ocfs2_xa_block_wipe_namevalue(struct ocfs2_xa_loc *loc)
{
	int i, offset;
	int namevalue_offset, first_namevalue_offset, namevalue_size;
	struct ocfs2_xattr_entry *entry = loc->xl_entry;
	struct ocfs2_xattr_header *xh = loc->xl_header;
	int count = le16_to_cpu(xh->xh_count);

	namevalue_offset = le16_to_cpu(entry->xe_name_offset);
	namevalue_size = namevalue_size_xe(entry);
	first_namevalue_offset = ocfs2_xa_get_free_start(loc);

	/* Shift the name+value pairs */
	memmove((char *)xh + first_namevalue_offset + namevalue_size,
		(char *)xh + first_namevalue_offset,
		namevalue_offset - first_namevalue_offset);
	memset((char *)xh + first_namevalue_offset, 0, namevalue_size);

	/* Now tell xh->xh_entries about it */
	for (i = 0; i < count; i++) {
		offset = le16_to_cpu(xh->xh_entries[i].xe_name_offset);
		if (offset <= namevalue_offset)
			le16_add_cpu(&xh->xh_entries[i].xe_name_offset,
				     namevalue_size);
	}

	/*
	 * Note that we don't update xh_free_start or xh_name_value_len
	 * because they're not used in block-stored xattrs.
	 */
}