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
struct objagg_obj {int /*<<< orphan*/  root_id; } ;
struct objagg {int /*<<< orphan*/  root_ida; int /*<<< orphan*/  hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void objagg_obj_root_id_free(struct objagg *objagg,
				    struct objagg_obj *objagg_obj)
{
	if (!objagg->hints)
		return;
	ida_free(&objagg->root_ida, objagg_obj->root_id);
}