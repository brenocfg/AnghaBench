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
struct xfs_fsop_geom {int /*<<< orphan*/  sick; int /*<<< orphan*/  checked; } ;
struct ioctl_sick_map {unsigned int sick_mask; int /*<<< orphan*/  ioctl_mask; } ;

/* Variables and functions */

__attribute__((used)) static inline void
xfgeo_health_tick(
	struct xfs_fsop_geom		*geo,
	unsigned int			sick,
	unsigned int			checked,
	const struct ioctl_sick_map	*m)
{
	if (checked & m->sick_mask)
		geo->checked |= m->ioctl_mask;
	if (sick & m->sick_mask)
		geo->sick |= m->ioctl_mask;
}