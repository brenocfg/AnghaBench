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
struct bpf_map {int map_flags; } ;

/* Variables and functions */
 int BPF_F_STACK_BUILD_ID ; 

__attribute__((used)) static inline bool stack_map_use_build_id(struct bpf_map *map)
{
	return (map->map_flags & BPF_F_STACK_BUILD_ID);
}