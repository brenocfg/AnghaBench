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
struct map_groups {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_groups__init (struct map_groups*,struct machine*) ; 
 struct map_groups* zalloc (int) ; 

struct map_groups *map_groups__new(struct machine *machine)
{
	struct map_groups *mg = zalloc(sizeof(*mg));

	if (mg != NULL)
		map_groups__init(mg, machine);

	return mg;
}