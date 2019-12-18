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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_scrub {int dummy; } ;
struct xchk_ag {int /*<<< orphan*/  agfl_bp; int /*<<< orphan*/  agf_bp; int /*<<< orphan*/  agi_bp; int /*<<< orphan*/  agno; } ;

/* Variables and functions */
 int xchk_ag_btcur_init (struct xfs_scrub*,struct xchk_ag*) ; 
 int xchk_ag_read_headers (struct xfs_scrub*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xchk_ag_init(
	struct xfs_scrub	*sc,
	xfs_agnumber_t		agno,
	struct xchk_ag		*sa)
{
	int			error;

	sa->agno = agno;
	error = xchk_ag_read_headers(sc, agno, &sa->agi_bp,
			&sa->agf_bp, &sa->agfl_bp);
	if (error)
		return error;

	return xchk_ag_btcur_init(sc, sa);
}