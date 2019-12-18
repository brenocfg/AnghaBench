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
struct uid_gid_map {unsigned int nr_extents; void* extent; void* forward; } ;
struct seq_file {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 unsigned int UID_GID_MAP_MAX_BASE_EXTENTS ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static void *m_start(struct seq_file *seq, loff_t *ppos,
		     struct uid_gid_map *map)
{
	loff_t pos = *ppos;
	unsigned extents = map->nr_extents;
	smp_rmb();

	if (pos >= extents)
		return NULL;

	if (extents <= UID_GID_MAP_MAX_BASE_EXTENTS)
		return &map->extent[pos];

	return &map->forward[pos];
}