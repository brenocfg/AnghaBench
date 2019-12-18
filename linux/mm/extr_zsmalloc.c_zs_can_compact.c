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
struct size_class {unsigned long objs_per_zspage; unsigned long pages_per_zspage; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_ALLOCATED ; 
 int /*<<< orphan*/  OBJ_USED ; 
 unsigned long zs_stat_get (struct size_class*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long zs_can_compact(struct size_class *class)
{
	unsigned long obj_wasted;
	unsigned long obj_allocated = zs_stat_get(class, OBJ_ALLOCATED);
	unsigned long obj_used = zs_stat_get(class, OBJ_USED);

	if (obj_allocated <= obj_used)
		return 0;

	obj_wasted = obj_allocated - obj_used;
	obj_wasted /= class->objs_per_zspage;

	return obj_wasted * class->pages_per_zspage;
}