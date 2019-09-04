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
struct xfs_iext_cursor {scalar_t__ pos; int /*<<< orphan*/  leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  cur_rec (struct xfs_iext_cursor*) ; 
 scalar_t__ xfs_iext_max_recs (struct xfs_ifork*) ; 
 scalar_t__ xfs_iext_rec_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool xfs_iext_valid(struct xfs_ifork *ifp,
		struct xfs_iext_cursor *cur)
{
	if (!cur->leaf)
		return false;
	if (cur->pos < 0 || cur->pos >= xfs_iext_max_recs(ifp))
		return false;
	if (xfs_iext_rec_is_empty(cur_rec(cur)))
		return false;
	return true;
}