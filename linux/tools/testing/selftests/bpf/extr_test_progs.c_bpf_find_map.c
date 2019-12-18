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
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int bpf_map__fd (struct bpf_map*) ; 
 struct bpf_map* bpf_object__find_map_by_name (struct bpf_object*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  test__fail () ; 

int bpf_find_map(const char *test, struct bpf_object *obj, const char *name)
{
	struct bpf_map *map;

	map = bpf_object__find_map_by_name(obj, name);
	if (!map) {
		printf("%s:FAIL:map '%s' not found\n", test, name);
		test__fail();
		return -1;
	}
	return bpf_map__fd(map);
}