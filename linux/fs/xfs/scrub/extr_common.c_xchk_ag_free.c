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
struct xfs_scrub {int /*<<< orphan*/  tp; } ;
struct xchk_ag {int /*<<< orphan*/  agno; int /*<<< orphan*/ * pag; int /*<<< orphan*/ * agi_bp; int /*<<< orphan*/ * agf_bp; int /*<<< orphan*/ * agfl_bp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLAGNUMBER ; 
 int /*<<< orphan*/  xchk_ag_btcur_free (struct xchk_ag*) ; 
 int /*<<< orphan*/  xfs_perag_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xchk_ag_free(
	struct xfs_scrub	*sc,
	struct xchk_ag		*sa)
{
	xchk_ag_btcur_free(sa);
	if (sa->agfl_bp) {
		xfs_trans_brelse(sc->tp, sa->agfl_bp);
		sa->agfl_bp = NULL;
	}
	if (sa->agf_bp) {
		xfs_trans_brelse(sc->tp, sa->agf_bp);
		sa->agf_bp = NULL;
	}
	if (sa->agi_bp) {
		xfs_trans_brelse(sc->tp, sa->agi_bp);
		sa->agi_bp = NULL;
	}
	if (sa->pag) {
		xfs_perag_put(sa->pag);
		sa->pag = NULL;
	}
	sa->agno = NULLAGNUMBER;
}