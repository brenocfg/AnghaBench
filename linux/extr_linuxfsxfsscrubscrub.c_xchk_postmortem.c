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
struct xfs_scrub {int /*<<< orphan*/  mp; TYPE_1__* sm; } ;
struct TYPE_2__ {int sm_flags; } ;

/* Variables and functions */
 int XFS_SCRUB_OFLAG_CORRUPT ; 
 int XFS_SCRUB_OFLAG_XCORRUPT ; 
 int /*<<< orphan*/  xfs_alert_ratelimited (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline void xchk_postmortem(struct xfs_scrub *sc)
{
	/*
	 * Userspace asked us to scrub something, it's broken, and we have no
	 * way of fixing it.  Scream in the logs.
	 */
	if (sc->sm->sm_flags & (XFS_SCRUB_OFLAG_CORRUPT |
				XFS_SCRUB_OFLAG_XCORRUPT))
		xfs_alert_ratelimited(sc->mp,
				"Corruption detected during scrub.");
}