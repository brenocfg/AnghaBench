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
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct xfs_perag {int pagf_agflreset; int /*<<< orphan*/  pagf_flcount; int /*<<< orphan*/  pag_agno; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct xfs_agf {scalar_t__ agf_flcount; int /*<<< orphan*/  agf_fllast; scalar_t__ agf_flfirst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_AGF_FLCOUNT ; 
 int XFS_AGF_FLFIRST ; 
 int XFS_AGF_FLLAST ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_agfl_reset (struct xfs_mount*,struct xfs_agf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_agfl_size (struct xfs_mount*) ; 
 int /*<<< orphan*/  xfs_alloc_log_agf (struct xfs_trans*,struct xfs_buf*,int) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_agfl_reset(
	struct xfs_trans	*tp,
	struct xfs_buf		*agbp,
	struct xfs_perag	*pag)
{
	struct xfs_mount	*mp = tp->t_mountp;
	struct xfs_agf		*agf = XFS_BUF_TO_AGF(agbp);

	ASSERT(pag->pagf_agflreset);
	trace_xfs_agfl_reset(mp, agf, 0, _RET_IP_);

	xfs_warn(mp,
	       "WARNING: Reset corrupted AGFL on AG %u. %d blocks leaked. "
	       "Please unmount and run xfs_repair.",
	         pag->pag_agno, pag->pagf_flcount);

	agf->agf_flfirst = 0;
	agf->agf_fllast = cpu_to_be32(xfs_agfl_size(mp) - 1);
	agf->agf_flcount = 0;
	xfs_alloc_log_agf(tp, agbp, XFS_AGF_FLFIRST | XFS_AGF_FLLAST |
				    XFS_AGF_FLCOUNT);

	pag->pagf_flcount = 0;
	pag->pagf_agflreset = false;
}