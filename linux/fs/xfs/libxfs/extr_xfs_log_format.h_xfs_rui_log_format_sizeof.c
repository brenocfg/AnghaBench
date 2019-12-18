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
struct xfs_rui_log_format {int dummy; } ;
struct xfs_map_extent {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t
xfs_rui_log_format_sizeof(
	unsigned int		nr)
{
	return sizeof(struct xfs_rui_log_format) +
			nr * sizeof(struct xfs_map_extent);
}