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
struct ocfs2_xa_loc {int xl_size; struct ocfs2_xattr_header* xl_header; } ;
struct TYPE_2__ {int /*<<< orphan*/  xe_name_offset; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xa_block_get_free_start(struct ocfs2_xa_loc *loc)
{
	struct ocfs2_xattr_header *xh = loc->xl_header;
	int i, count = le16_to_cpu(xh->xh_count);
	int offset, free_start = loc->xl_size;

	for (i = 0; i < count; i++) {
		offset = le16_to_cpu(xh->xh_entries[i].xe_name_offset);
		if (offset < free_start)
			free_start = offset;
	}

	return free_start;
}