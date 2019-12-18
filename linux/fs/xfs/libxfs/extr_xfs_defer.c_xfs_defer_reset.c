#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xfs_trans {int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_dfops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_TRANS_LOWMODE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfs_defer_reset(
	struct xfs_trans	*tp)
{
	ASSERT(list_empty(&tp->t_dfops));

	/*
	 * Low mode state transfers across transaction rolls to mirror dfops
	 * lifetime. Clear it now that dfops is reset.
	 */
	tp->t_flags &= ~XFS_TRANS_LOWMODE;
}