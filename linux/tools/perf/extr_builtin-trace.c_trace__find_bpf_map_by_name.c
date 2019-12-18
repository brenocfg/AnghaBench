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
struct trace {int /*<<< orphan*/ * bpf_obj; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 struct bpf_map* bpf_object__find_map_by_name (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct bpf_map *trace__find_bpf_map_by_name(struct trace *trace, const char *name)
{
	if (trace->bpf_obj == NULL)
		return NULL;

	return bpf_object__find_map_by_name(trace->bpf_obj, name);
}