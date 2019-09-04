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
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_perag {int /*<<< orphan*/  pagf_fstrms; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct xfs_perag* xfs_perag_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

__attribute__((used)) static void
xfs_filestream_put_ag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agno)
{
	struct xfs_perag *pag;

	pag = xfs_perag_get(mp, agno);
	atomic_dec(&pag->pagf_fstrms);
	xfs_perag_put(pag);
}