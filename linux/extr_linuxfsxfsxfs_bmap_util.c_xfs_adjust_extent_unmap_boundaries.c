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
typedef  scalar_t__ xfs_fileoff_t ;
typedef  scalar_t__ xfs_extlen_t ;
struct TYPE_2__ {scalar_t__ sb_rextsize; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int /*<<< orphan*/  div_u64_rem (scalar_t__,scalar_t__,scalar_t__*) ; 
 int xfs_bmapi_read (struct xfs_inode*,scalar_t__,int,struct xfs_bmbt_irec*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_adjust_extent_unmap_boundaries(
	struct xfs_inode	*ip,
	xfs_fileoff_t		*startoffset_fsb,
	xfs_fileoff_t		*endoffset_fsb)
{
	struct xfs_mount	*mp = ip->i_mount;
	struct xfs_bmbt_irec	imap;
	int			nimap, error;
	xfs_extlen_t		mod = 0;

	nimap = 1;
	error = xfs_bmapi_read(ip, *startoffset_fsb, 1, &imap, &nimap, 0);
	if (error)
		return error;

	if (nimap && imap.br_startblock != HOLESTARTBLOCK) {
		ASSERT(imap.br_startblock != DELAYSTARTBLOCK);
		div_u64_rem(imap.br_startblock, mp->m_sb.sb_rextsize, &mod);
		if (mod)
			*startoffset_fsb += mp->m_sb.sb_rextsize - mod;
	}

	nimap = 1;
	error = xfs_bmapi_read(ip, *endoffset_fsb - 1, 1, &imap, &nimap, 0);
	if (error)
		return error;

	if (nimap && imap.br_startblock != HOLESTARTBLOCK) {
		ASSERT(imap.br_startblock != DELAYSTARTBLOCK);
		mod++;
		if (mod && mod != mp->m_sb.sb_rextsize)
			*endoffset_fsb -= mod;
	}

	return 0;
}