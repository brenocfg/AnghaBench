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
struct ocfs2_xa_loc {TYPE_1__* xl_ops; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int (* xlo_journal_access ) (int /*<<< orphan*/ *,struct ocfs2_xa_loc*,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct ocfs2_xa_loc*,int) ; 

__attribute__((used)) static int ocfs2_xa_journal_access(handle_t *handle, struct ocfs2_xa_loc *loc,
				   int type)
{
	return loc->xl_ops->xlo_journal_access(handle, loc, type);
}