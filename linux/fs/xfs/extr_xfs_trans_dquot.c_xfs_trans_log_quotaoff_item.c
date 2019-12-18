#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  t_flags; } ;
typedef  TYPE_2__ xfs_trans_t ;
struct TYPE_6__ {int /*<<< orphan*/  li_flags; } ;
struct TYPE_8__ {TYPE_1__ qql_item; } ;
typedef  TYPE_3__ xfs_qoff_logitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_trans_log_quotaoff_item(
	xfs_trans_t		*tp,
	xfs_qoff_logitem_t	*qlp)
{
	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &qlp->qql_item.li_flags);
}