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
struct TYPE_2__ {int /*<<< orphan*/  pag; int /*<<< orphan*/  agno; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  tp; int /*<<< orphan*/  mp; } ;
struct xfs_alloc_arg {int alignment; int /*<<< orphan*/  pag; int /*<<< orphan*/  agno; int /*<<< orphan*/  tp; int /*<<< orphan*/  mp; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_ALLOC_FLAG_NOSHRINK ; 
 int xfs_alloc_fix_freelist (struct xfs_alloc_arg*,int /*<<< orphan*/ ) ; 

int
xrep_fix_freelist(
	struct xfs_scrub	*sc,
	bool			can_shrink)
{
	struct xfs_alloc_arg	args = {0};

	args.mp = sc->mp;
	args.tp = sc->tp;
	args.agno = sc->sa.agno;
	args.alignment = 1;
	args.pag = sc->sa.pag;

	return xfs_alloc_fix_freelist(&args,
			can_shrink ? 0 : XFS_ALLOC_FLAG_NOSHRINK);
}