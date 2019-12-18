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
struct xfs_perag {int dummy; } ;
struct xfs_ag_geometry {int /*<<< orphan*/  ag_sick; int /*<<< orphan*/  ag_checked; } ;
struct ioctl_sick_map {int sick_mask; int /*<<< orphan*/  ioctl_mask; } ;

/* Variables and functions */
 struct ioctl_sick_map* ag_map ; 
 int /*<<< orphan*/  xfs_ag_measure_sickness (struct xfs_perag*,unsigned int*,unsigned int*) ; 

void
xfs_ag_geom_health(
	struct xfs_perag		*pag,
	struct xfs_ag_geometry		*ageo)
{
	const struct ioctl_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	ageo->ag_sick = 0;
	ageo->ag_checked = 0;

	xfs_ag_measure_sickness(pag, &sick, &checked);
	for (m = ag_map; m->sick_mask; m++) {
		if (checked & m->sick_mask)
			ageo->ag_checked |= m->ioctl_mask;
		if (sick & m->sick_mask)
			ageo->ag_sick |= m->ioctl_mask;
	}
}