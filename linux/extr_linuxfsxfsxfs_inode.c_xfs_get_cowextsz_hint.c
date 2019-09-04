#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_extlen_t ;
struct TYPE_2__ {int di_flags2; scalar_t__ di_cowextsize; } ;
struct xfs_inode {TYPE_1__ i_d; } ;

/* Variables and functions */
 scalar_t__ XFS_DEFAULT_COWEXTSZ_HINT ; 
 int XFS_DIFLAG2_COWEXTSIZE ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ xfs_get_extsz_hint (struct xfs_inode*) ; 

xfs_extlen_t
xfs_get_cowextsz_hint(
	struct xfs_inode	*ip)
{
	xfs_extlen_t		a, b;

	a = 0;
	if (ip->i_d.di_flags2 & XFS_DIFLAG2_COWEXTSIZE)
		a = ip->i_d.di_cowextsize;
	b = xfs_get_extsz_hint(ip);

	a = max(a, b);
	if (a == 0)
		return XFS_DEFAULT_COWEXTSZ_HINT;
	return a;
}