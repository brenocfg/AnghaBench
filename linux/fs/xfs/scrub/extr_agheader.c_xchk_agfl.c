#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_4__ {int /*<<< orphan*/  agf_bp; int /*<<< orphan*/  agfl_bp; int /*<<< orphan*/  agi_bp; int /*<<< orphan*/  agno; } ;
struct xfs_scrub {TYPE_2__ sa; int /*<<< orphan*/  mp; TYPE_1__* sm; } ;
struct xfs_agf {int /*<<< orphan*/  agf_flcount; } ;
struct xchk_agfl_info {unsigned int sz_entries; scalar_t__* entries; unsigned int nr_entries; struct xfs_scrub* sc; } ;
typedef  int /*<<< orphan*/  sai ;
struct TYPE_3__ {int sm_flags; int /*<<< orphan*/  sm_agno; } ;

/* Variables and functions */
 int ECANCELED ; 
 int EFSCORRUPTED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_MAYFAIL ; 
 int /*<<< orphan*/  XFS_AGFL_BLOCK (int /*<<< orphan*/ ) ; 
 struct xfs_agf* XFS_BUF_TO_AGF (int /*<<< orphan*/ ) ; 
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__*) ; 
 scalar_t__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xchk_agfl_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sort (scalar_t__*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xchk_ag_read_headers (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xchk_agblock_cmp ; 
 int /*<<< orphan*/  xchk_agfl_block ; 
 int /*<<< orphan*/  xchk_agfl_xref (struct xfs_scrub*) ; 
 int /*<<< orphan*/  xchk_block_set_corrupt (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_buffer_recheck (struct xfs_scrub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xchk_process_error (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned int xfs_agfl_size (int /*<<< orphan*/ ) ; 
 int xfs_agfl_walk (int /*<<< orphan*/ ,struct xfs_agf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xchk_agfl_info*) ; 

int
xchk_agfl(
	struct xfs_scrub	*sc)
{
	struct xchk_agfl_info	sai;
	struct xfs_agf		*agf;
	xfs_agnumber_t		agno;
	unsigned int		agflcount;
	unsigned int		i;
	int			error;

	agno = sc->sa.agno = sc->sm->sm_agno;
	error = xchk_ag_read_headers(sc, agno, &sc->sa.agi_bp,
			&sc->sa.agf_bp, &sc->sa.agfl_bp);
	if (!xchk_process_error(sc, agno, XFS_AGFL_BLOCK(sc->mp), &error))
		goto out;
	if (!sc->sa.agf_bp)
		return -EFSCORRUPTED;
	xchk_buffer_recheck(sc, sc->sa.agfl_bp);

	xchk_agfl_xref(sc);

	if (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		goto out;

	/* Allocate buffer to ensure uniqueness of AGFL entries. */
	agf = XFS_BUF_TO_AGF(sc->sa.agf_bp);
	agflcount = be32_to_cpu(agf->agf_flcount);
	if (agflcount > xfs_agfl_size(sc->mp)) {
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
		goto out;
	}
	memset(&sai, 0, sizeof(sai));
	sai.sc = sc;
	sai.sz_entries = agflcount;
	sai.entries = kmem_zalloc(sizeof(xfs_agblock_t) * agflcount,
			KM_MAYFAIL);
	if (!sai.entries) {
		error = -ENOMEM;
		goto out;
	}

	/* Check the blocks in the AGFL. */
	error = xfs_agfl_walk(sc->mp, XFS_BUF_TO_AGF(sc->sa.agf_bp),
			sc->sa.agfl_bp, xchk_agfl_block, &sai);
	if (error == -ECANCELED) {
		error = 0;
		goto out_free;
	}
	if (error)
		goto out_free;

	if (agflcount != sai.nr_entries) {
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
		goto out_free;
	}

	/* Sort entries, check for duplicates. */
	sort(sai.entries, sai.nr_entries, sizeof(sai.entries[0]),
			xchk_agblock_cmp, NULL);
	for (i = 1; i < sai.nr_entries; i++) {
		if (sai.entries[i] == sai.entries[i - 1]) {
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);
			break;
		}
	}

out_free:
	kmem_free(sai.entries);
out:
	return error;
}