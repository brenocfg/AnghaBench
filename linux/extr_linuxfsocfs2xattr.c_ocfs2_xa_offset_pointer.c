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
struct ocfs2_xa_loc {int xl_size; TYPE_1__* xl_ops; } ;
struct TYPE_2__ {void* (* xlo_offset_pointer ) (struct ocfs2_xa_loc*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* stub1 (struct ocfs2_xa_loc*,int) ; 

__attribute__((used)) static void *ocfs2_xa_offset_pointer(struct ocfs2_xa_loc *loc, int offset)
{
	BUG_ON(offset >= loc->xl_size);
	return loc->xl_ops->xlo_offset_pointer(loc, offset);
}