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
struct TYPE_2__ {int /*<<< orphan*/  (* xlo_journal_dirty ) (int /*<<< orphan*/ *,struct ocfs2_xa_loc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct ocfs2_xa_loc*) ; 

__attribute__((used)) static void ocfs2_xa_journal_dirty(handle_t *handle, struct ocfs2_xa_loc *loc)
{
	loc->xl_ops->xlo_journal_dirty(handle, loc);
}