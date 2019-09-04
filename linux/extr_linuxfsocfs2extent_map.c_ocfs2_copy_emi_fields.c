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
struct ocfs2_extent_map_item {int /*<<< orphan*/  ei_flags; int /*<<< orphan*/  ei_clusters; int /*<<< orphan*/  ei_phys; int /*<<< orphan*/  ei_cpos; } ;

/* Variables and functions */

__attribute__((used)) static void ocfs2_copy_emi_fields(struct ocfs2_extent_map_item *dest,
				  struct ocfs2_extent_map_item *src)
{
	dest->ei_cpos = src->ei_cpos;
	dest->ei_phys = src->ei_phys;
	dest->ei_clusters = src->ei_clusters;
	dest->ei_flags = src->ei_flags;
}