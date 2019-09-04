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
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {int /*<<< orphan*/  leaf; scalar_t__ pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_iext_find_first_leaf (struct xfs_ifork*) ; 

void
xfs_iext_first(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur)
{
	cur->pos = 0;
	cur->leaf = xfs_iext_find_first_leaf(ifp);
}