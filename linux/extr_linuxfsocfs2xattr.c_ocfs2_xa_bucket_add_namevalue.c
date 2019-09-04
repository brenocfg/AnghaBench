#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ocfs2_xattr_header {int /*<<< orphan*/  xh_name_value_len; void* xh_free_start; } ;
struct ocfs2_xa_loc {TYPE_1__* xl_entry; TYPE_2__* xl_inode; struct ocfs2_xattr_header* xl_header; } ;
struct TYPE_4__ {struct super_block* i_sb; } ;
struct TYPE_3__ {void* xe_name_offset; } ;

/* Variables and functions */
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int ocfs2_bucket_align_free_start (struct super_block*,int,int) ; 
 int ocfs2_xa_get_free_start (struct ocfs2_xa_loc*) ; 

__attribute__((used)) static void ocfs2_xa_bucket_add_namevalue(struct ocfs2_xa_loc *loc, int size)
{
	int free_start = ocfs2_xa_get_free_start(loc);
	struct ocfs2_xattr_header *xh = loc->xl_header;
	struct super_block *sb = loc->xl_inode->i_sb;
	int nameval_offset;

	free_start = ocfs2_bucket_align_free_start(sb, free_start, size);
	nameval_offset = free_start - size;
	loc->xl_entry->xe_name_offset = cpu_to_le16(nameval_offset);
	xh->xh_free_start = cpu_to_le16(nameval_offset);
	le16_add_cpu(&xh->xh_name_value_len, size);

}