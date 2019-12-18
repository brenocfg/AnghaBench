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
struct trace_eval_map {int dummy; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_event_eval_update (struct trace_eval_map**,int) ; 
 int /*<<< orphan*/  trace_insert_eval_map_file (struct module*,struct trace_eval_map**,int) ; 

__attribute__((used)) static void trace_insert_eval_map(struct module *mod,
				  struct trace_eval_map **start, int len)
{
	struct trace_eval_map **map;

	if (len <= 0)
		return;

	map = start;

	trace_event_eval_update(map, len);

	trace_insert_eval_map_file(mod, start, len);
}