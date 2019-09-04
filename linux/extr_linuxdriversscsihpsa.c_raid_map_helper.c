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
typedef  int u32 ;
struct raid_map_data {int /*<<< orphan*/  data_disks_per_row; int /*<<< orphan*/  layout_map_count; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid_map_helper(struct raid_map_data *map,
		int offload_to_mirror, u32 *map_index, u32 *current_group)
{
	if (offload_to_mirror == 0)  {
		/* use physical disk in the first mirrored group. */
		*map_index %= le16_to_cpu(map->data_disks_per_row);
		return;
	}
	do {
		/* determine mirror group that *map_index indicates */
		*current_group = *map_index /
			le16_to_cpu(map->data_disks_per_row);
		if (offload_to_mirror == *current_group)
			continue;
		if (*current_group < le16_to_cpu(map->layout_map_count) - 1) {
			/* select map index from next group */
			*map_index += le16_to_cpu(map->data_disks_per_row);
			(*current_group)++;
		} else {
			/* select map index from first group */
			*map_index %= le16_to_cpu(map->data_disks_per_row);
			*current_group = 0;
		}
	} while (offload_to_mirror != *current_group);
}