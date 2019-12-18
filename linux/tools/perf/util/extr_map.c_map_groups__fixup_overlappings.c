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
struct map_groups {int /*<<< orphan*/  maps; } ;
struct map {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int maps__fixup_overlappings (int /*<<< orphan*/ *,struct map*,int /*<<< orphan*/ *) ; 

int map_groups__fixup_overlappings(struct map_groups *mg, struct map *map,
				   FILE *fp)
{
	return maps__fixup_overlappings(&mg->maps, map, fp);
}