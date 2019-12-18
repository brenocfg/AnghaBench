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
typedef  int /*<<< orphan*/  xfs_rtalloc_query_range_fn ;
struct xfs_trans {TYPE_1__* t_mountp; } ;
struct xfs_rtalloc_rec {scalar_t__ ar_extcount; scalar_t__ ar_startext; } ;
struct TYPE_4__ {scalar_t__ sb_rextents; } ;
struct TYPE_3__ {TYPE_2__ m_sb; } ;

/* Variables and functions */
 int xfs_rtalloc_query_range (struct xfs_trans*,struct xfs_rtalloc_rec*,struct xfs_rtalloc_rec*,int /*<<< orphan*/ ,void*) ; 

int
xfs_rtalloc_query_all(
	struct xfs_trans		*tp,
	xfs_rtalloc_query_range_fn	fn,
	void				*priv)
{
	struct xfs_rtalloc_rec		keys[2];

	keys[0].ar_startext = 0;
	keys[1].ar_startext = tp->t_mountp->m_sb.sb_rextents - 1;
	keys[0].ar_extcount = keys[1].ar_extcount = 0;

	return xfs_rtalloc_query_range(tp, &keys[0], &keys[1], fn, priv);
}