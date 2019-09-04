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
typedef  int /*<<< orphan*/  xfs_ino_t ;
struct xfs_scrub {int /*<<< orphan*/  ip; int /*<<< orphan*/  tp; struct xfs_mount* mp; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_INO_TO_AGBNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_INO_TO_AGNO (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_ino_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_ino_set_preen (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_xref_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ xfs_is_reflink_inode (int /*<<< orphan*/ ) ; 
 int xfs_reflink_inode_has_shared_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xfs_sb_version_hasreflink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xchk_inode_check_reflink_iflag(
	struct xfs_scrub	*sc,
	xfs_ino_t		ino)
{
	struct xfs_mount	*mp = sc->mp;
	bool			has_shared;
	int			error;

	if (!xfs_sb_version_hasreflink(&mp->m_sb))
		return;

	error = xfs_reflink_inode_has_shared_extents(sc->tp, sc->ip,
			&has_shared);
	if (!xchk_xref_process_error(sc, XFS_INO_TO_AGNO(mp, ino),
			XFS_INO_TO_AGBNO(mp, ino), &error))
		return;
	if (xfs_is_reflink_inode(sc->ip) && !has_shared)
		xchk_ino_set_preen(sc, ino);
	else if (!xfs_is_reflink_inode(sc->ip) && has_shared)
		xchk_ino_set_corrupt(sc, ino);
}