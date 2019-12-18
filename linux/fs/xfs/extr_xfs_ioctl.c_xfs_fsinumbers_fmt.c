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
struct xfs_inumbers {int dummy; } ;
struct xfs_inogrp {int dummy; } ;
struct xfs_ibulk {int /*<<< orphan*/  ubuffer; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct xfs_inogrp*,int) ; 
 int xfs_ibulk_advance (struct xfs_ibulk*,int) ; 
 int /*<<< orphan*/  xfs_inumbers_to_inogrp (struct xfs_inogrp*,struct xfs_inumbers const*) ; 

int
xfs_fsinumbers_fmt(
	struct xfs_ibulk		*breq,
	const struct xfs_inumbers	*igrp)
{
	struct xfs_inogrp		ig1;

	xfs_inumbers_to_inogrp(&ig1, igrp);
	if (copy_to_user(breq->ubuffer, &ig1, sizeof(struct xfs_inogrp)))
		return -EFAULT;
	return xfs_ibulk_advance(breq, sizeof(struct xfs_inogrp));
}