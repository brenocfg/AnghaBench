#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct parse_events_array {unsigned int nr_ranges; TYPE_1__* ranges; } ;
struct parse_events_term {struct parse_events_array array; } ;
struct bpf_map_def {unsigned int max_entries; } ;
struct bpf_map {int dummy; } ;
struct TYPE_2__ {unsigned int start; size_t length; } ;

/* Variables and functions */
 int BPF_LOADER_ERRNO__INTERNAL ; 
 int BPF_LOADER_ERRNO__OBJCONF_MAP_IDX2BIG ; 
 scalar_t__ IS_ERR (struct bpf_map_def const*) ; 
 struct bpf_map_def* bpf_map__def (struct bpf_map*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int
config_map_indices_range_check(struct parse_events_term *term,
			       struct bpf_map *map,
			       const char *map_name)
{
	struct parse_events_array *array = &term->array;
	const struct bpf_map_def *def;
	unsigned int i;

	if (!array->nr_ranges)
		return 0;
	if (!array->ranges) {
		pr_debug("ERROR: map %s: array->nr_ranges is %d but range array is NULL\n",
			 map_name, (int)array->nr_ranges);
		return -BPF_LOADER_ERRNO__INTERNAL;
	}

	def = bpf_map__def(map);
	if (IS_ERR(def)) {
		pr_debug("ERROR: Unable to get map definition from '%s'\n",
			 map_name);
		return -BPF_LOADER_ERRNO__INTERNAL;
	}

	for (i = 0; i < array->nr_ranges; i++) {
		unsigned int start = array->ranges[i].start;
		size_t length = array->ranges[i].length;
		unsigned int idx = start + length - 1;

		if (idx >= def->max_entries) {
			pr_debug("ERROR: index %d too large\n", idx);
			return -BPF_LOADER_ERRNO__OBJCONF_MAP_IDX2BIG;
		}
	}
	return 0;
}