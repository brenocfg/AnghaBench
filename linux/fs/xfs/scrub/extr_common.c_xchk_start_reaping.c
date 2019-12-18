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
struct xfs_scrub {int /*<<< orphan*/  flags; int /*<<< orphan*/  mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCHK_REAPING_DISABLED ; 
 int /*<<< orphan*/  xfs_start_block_reaping (int /*<<< orphan*/ ) ; 

void
xchk_start_reaping(
	struct xfs_scrub	*sc)
{
	xfs_start_block_reaping(sc->mp);
	sc->flags &= ~XCHK_REAPING_DISABLED;
}