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

/* Variables and functions */
 struct map* maps__first (int /*<<< orphan*/ *) ; 

struct map *map_groups__first(struct map_groups *mg)
{
	return maps__first(&mg->maps);
}