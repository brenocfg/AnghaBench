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
 scalar_t__ IS_ERR (struct objagg_obj*) ; 
 struct objagg_obj* __objagg_obj_get (struct objagg*,void*) ; 
 int /*<<< orphan*/  objagg_obj_stats_inc (struct objagg_obj*) ; 
 int /*<<< orphan*/  trace_objagg_obj_get (struct objagg*,struct objagg_obj*,int /*<<< orphan*/ ) ; 

struct objagg_obj *objagg_obj_get(struct objagg *objagg, void *obj)
{
	struct objagg_obj *objagg_obj;

	objagg_obj = __objagg_obj_get(objagg, obj);
	if (IS_ERR(objagg_obj))
		return objagg_obj;
	objagg_obj_stats_inc(objagg_obj);
	trace_objagg_obj_get(objagg, objagg_obj, objagg_obj->refcount);
	return objagg_obj;
}