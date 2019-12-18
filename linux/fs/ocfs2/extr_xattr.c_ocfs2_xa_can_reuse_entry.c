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
struct ocfs2_xattr_info {int dummy; } ;
struct ocfs2_xa_loc {TYPE_1__* xl_ops; } ;
struct TYPE_2__ {int (* xlo_can_reuse ) (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*) ;} ;

/* Variables and functions */
 int stub1 (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*) ; 

__attribute__((used)) static int ocfs2_xa_can_reuse_entry(struct ocfs2_xa_loc *loc,
				    struct ocfs2_xattr_info *xi)
{
	return loc->xl_ops->xlo_can_reuse(loc, xi);
}