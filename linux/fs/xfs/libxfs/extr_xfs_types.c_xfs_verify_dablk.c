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
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */

bool
xfs_verify_dablk(
	struct xfs_mount	*mp,
	xfs_fileoff_t		dabno)
{
	xfs_dablk_t		max_dablk = -1U;

	return dabno <= max_dablk;
}