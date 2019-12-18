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
struct xfs_pwork {int /*<<< orphan*/  pctl; } ;

/* Variables and functions */
 int xfs_pwork_ctl_want_abort (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
xfs_pwork_want_abort(
	struct xfs_pwork	*pwork)
{
	return xfs_pwork_ctl_want_abort(pwork->pctl);
}