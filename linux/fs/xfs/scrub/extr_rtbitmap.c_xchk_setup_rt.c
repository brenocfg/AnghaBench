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
struct xfs_scrub {int ilock_flags; int /*<<< orphan*/  ip; TYPE_1__* mp; } ;
struct xfs_inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m_rbmip; } ;

/* Variables and functions */
 int XFS_ILOCK_EXCL ; 
 int XFS_ILOCK_RTBITMAP ; 
 int xchk_setup_fs (struct xfs_scrub*,struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_ilock (int /*<<< orphan*/ ,int) ; 

int
xchk_setup_rt(
	struct xfs_scrub	*sc,
	struct xfs_inode	*ip)
{
	int			error;

	error = xchk_setup_fs(sc, ip);
	if (error)
		return error;

	sc->ilock_flags = XFS_ILOCK_EXCL | XFS_ILOCK_RTBITMAP;
	sc->ip = sc->mp->m_rbmip;
	xfs_ilock(sc->ip, sc->ilock_flags);

	return 0;
}