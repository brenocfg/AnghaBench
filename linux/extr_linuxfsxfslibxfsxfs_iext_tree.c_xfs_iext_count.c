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
typedef  int xfs_extnum_t ;
struct xfs_ifork {int if_bytes; } ;
struct xfs_iext_rec {int dummy; } ;

/* Variables and functions */

inline xfs_extnum_t xfs_iext_count(struct xfs_ifork *ifp)
{
	return ifp->if_bytes / sizeof(struct xfs_iext_rec);
}