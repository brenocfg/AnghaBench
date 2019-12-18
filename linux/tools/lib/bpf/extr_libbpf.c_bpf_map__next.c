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
struct bpf_object {struct bpf_map* maps; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 struct bpf_map* __bpf_map__iter (struct bpf_map const*,struct bpf_object const*,int) ; 

struct bpf_map *
bpf_map__next(const struct bpf_map *prev, const struct bpf_object *obj)
{
	if (prev == NULL)
		return obj->maps;

	return __bpf_map__iter(prev, obj, 1);
}