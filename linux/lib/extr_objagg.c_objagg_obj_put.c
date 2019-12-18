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
struct objagg_obj {int /*<<< orphan*/  refcount; } ;
struct objagg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __objagg_obj_put (struct objagg*,struct objagg_obj*) ; 
 int /*<<< orphan*/  objagg_obj_stats_dec (struct objagg_obj*) ; 
 int /*<<< orphan*/  trace_objagg_obj_put (struct objagg*,struct objagg_obj*,int /*<<< orphan*/ ) ; 

void objagg_obj_put(struct objagg *objagg, struct objagg_obj *objagg_obj)
{
	trace_objagg_obj_put(objagg, objagg_obj, objagg_obj->refcount);
	objagg_obj_stats_dec(objagg_obj);
	__objagg_obj_put(objagg, objagg_obj);
}