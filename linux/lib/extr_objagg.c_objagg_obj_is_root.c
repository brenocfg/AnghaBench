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
struct objagg_obj {int /*<<< orphan*/  parent; } ;

/* Variables and functions */

__attribute__((used)) static bool objagg_obj_is_root(const struct objagg_obj *objagg_obj)
{
	/* Nesting is not supported, so we can use ->parent
	 * to figure out if the object is root.
	 */
	return !objagg_obj->parent;
}