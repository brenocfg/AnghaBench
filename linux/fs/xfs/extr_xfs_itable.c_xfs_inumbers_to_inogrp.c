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
struct xfs_inumbers {int /*<<< orphan*/  xi_allocmask; int /*<<< orphan*/  xi_alloccount; int /*<<< orphan*/  xi_startino; } ;
struct xfs_inogrp {int /*<<< orphan*/  xi_allocmask; int /*<<< orphan*/  xi_alloccount; int /*<<< orphan*/  xi_startino; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xfs_inogrp*,int /*<<< orphan*/ ,int) ; 

void
xfs_inumbers_to_inogrp(
	struct xfs_inogrp		*ig1,
	const struct xfs_inumbers	*ig)
{
	/* memset is needed here because of padding holes in the structure. */
	memset(ig1, 0, sizeof(struct xfs_inogrp));
	ig1->xi_startino = ig->xi_startino;
	ig1->xi_alloccount = ig->xi_alloccount;
	ig1->xi_allocmask = ig->xi_allocmask;
}