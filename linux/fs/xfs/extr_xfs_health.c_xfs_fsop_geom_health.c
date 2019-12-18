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
struct xfs_fsop_geom {int /*<<< orphan*/  checked; int /*<<< orphan*/  sick; } ;
struct ioctl_sick_map {scalar_t__ sick_mask; } ;

/* Variables and functions */
 struct ioctl_sick_map* fs_map ; 
 struct ioctl_sick_map* rt_map ; 
 int /*<<< orphan*/  xfgeo_health_tick (struct xfs_fsop_geom*,unsigned int,unsigned int,struct ioctl_sick_map const*) ; 
 int /*<<< orphan*/  xfs_fs_measure_sickness (struct xfs_mount*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  xfs_rt_measure_sickness (struct xfs_mount*,unsigned int*,unsigned int*) ; 

void
xfs_fsop_geom_health(
	struct xfs_mount		*mp,
	struct xfs_fsop_geom		*geo)
{
	const struct ioctl_sick_map	*m;
	unsigned int			sick;
	unsigned int			checked;

	geo->sick = 0;
	geo->checked = 0;

	xfs_fs_measure_sickness(mp, &sick, &checked);
	for (m = fs_map; m->sick_mask; m++)
		xfgeo_health_tick(geo, sick, checked, m);

	xfs_rt_measure_sickness(mp, &sick, &checked);
	for (m = rt_map; m->sick_mask; m++)
		xfgeo_health_tick(geo, sick, checked, m);
}