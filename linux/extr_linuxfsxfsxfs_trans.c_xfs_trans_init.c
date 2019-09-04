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
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_trans_resv_calc (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_trace_reservations (struct xfs_mount*) ; 

void
xfs_trans_init(
	struct xfs_mount	*mp)
{
	xfs_trans_resv_calc(mp, M_RES(mp));
	xfs_trans_trace_reservations(mp);
}