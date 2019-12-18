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
struct objagg_obj {int dummy; } ;
struct objagg {int /*<<< orphan*/  ht_params; int /*<<< orphan*/  obj_ht; } ;

/* Variables and functions */
 struct objagg_obj* rhashtable_lookup_fast (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct objagg_obj *objagg_obj_lookup(struct objagg *objagg, void *obj)
{
	return rhashtable_lookup_fast(&objagg->obj_ht, obj, objagg->ht_params);
}