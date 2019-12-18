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
struct TYPE_2__ {int inner_map_idx; scalar_t__ max_entries; } ;
struct bpf_map_data {TYPE_1__ def; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NR_TESTS ; 
 int array_of_lru_hashs_idx ; 
 scalar_t__ check_test_flags (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int inner_lru_hash_idx ; 
 scalar_t__ inner_lru_hash_size ; 
 int lru_hash_lookup_idx ; 
 scalar_t__ num_map_entries ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char** test_map_names ; 

__attribute__((used)) static void fixup_map(struct bpf_map_data *map, int idx)
{
	int i;

	if (!strcmp("inner_lru_hash_map", map->name)) {
		inner_lru_hash_idx = idx;
		inner_lru_hash_size = map->def.max_entries;
	}

	if (!strcmp("array_of_lru_hashs", map->name)) {
		if (inner_lru_hash_idx == -1) {
			printf("inner_lru_hash_map must be defined before array_of_lru_hashs\n");
			exit(1);
		}
		map->def.inner_map_idx = inner_lru_hash_idx;
		array_of_lru_hashs_idx = idx;
	}

	if (!strcmp("lru_hash_lookup_map", map->name))
		lru_hash_lookup_idx = idx;

	if (num_map_entries <= 0)
		return;

	inner_lru_hash_size = num_map_entries;

	/* Only change the max_entries for the enabled test(s) */
	for (i = 0; i < NR_TESTS; i++) {
		if (!strcmp(test_map_names[i], map->name) &&
		    (check_test_flags(i))) {
			map->def.max_entries = num_map_entries;
		}
	}
}