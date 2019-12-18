#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_xattr_value_root {int dummy; } ;
struct ocfs2_xattr_value_buf {struct ocfs2_xattr_value_root* vb_xv; } ;
struct ocfs2_xa_loc {TYPE_1__* xl_ops; TYPE_2__* xl_entry; } ;
struct TYPE_5__ {int /*<<< orphan*/  xe_name_len; int /*<<< orphan*/  xe_name_offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* xlo_fill_value_buf ) (struct ocfs2_xa_loc*,struct ocfs2_xattr_value_buf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ OCFS2_XATTR_ROOT_SIZE ; 
 int OCFS2_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ namevalue_size_xe (TYPE_2__*) ; 
 scalar_t__ ocfs2_xa_offset_pointer (struct ocfs2_xa_loc*,int) ; 
 int ocfs2_xattr_is_local (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_xa_loc*,struct ocfs2_xattr_value_buf*) ; 

__attribute__((used)) static void ocfs2_xa_fill_value_buf(struct ocfs2_xa_loc *loc,
				    struct ocfs2_xattr_value_buf *vb)
{
	int nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	int name_size = OCFS2_XATTR_SIZE(loc->xl_entry->xe_name_len);

	/* Value bufs are for value trees */
	BUG_ON(ocfs2_xattr_is_local(loc->xl_entry));
	BUG_ON(namevalue_size_xe(loc->xl_entry) !=
	       (name_size + OCFS2_XATTR_ROOT_SIZE));

	loc->xl_ops->xlo_fill_value_buf(loc, vb);
	vb->vb_xv =
		(struct ocfs2_xattr_value_root *)ocfs2_xa_offset_pointer(loc,
							nameval_offset +
							name_size);
}