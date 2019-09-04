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
struct xfs_mount {int dummy; } ;
struct xchk_ag {int /*<<< orphan*/  agno; scalar_t__ pag; } ;

/* Variables and functions */
 scalar_t__ xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 

void
xchk_perag_get(
	struct xfs_mount	*mp,
	struct xchk_ag		*sa)
{
	if (!sa->pag)
		sa->pag = xfs_perag_get(mp, sa->agno);
}