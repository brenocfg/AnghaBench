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
struct ocfs2_xattr_value_buf {TYPE_1__* vb_xv; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  xr_clusters; } ;

/* Variables and functions */
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xa_fill_value_buf (struct ocfs2_xa_loc*,struct ocfs2_xattr_value_buf*) ; 
 scalar_t__ ocfs2_xattr_is_local (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ocfs2_xa_value_clusters(struct ocfs2_xa_loc *loc)
{
	struct ocfs2_xattr_value_buf vb;

	if (ocfs2_xattr_is_local(loc->xl_entry))
		return 0;

	ocfs2_xa_fill_value_buf(loc, &vb);
	return le32_to_cpu(vb.vb_xv->xr_clusters);
}