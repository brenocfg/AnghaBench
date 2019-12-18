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
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_obj_config_map_for_key ; 
 int bpf_map_config_foreach_key (struct bpf_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
apply_obj_config_map(struct bpf_map *map)
{
	return bpf_map_config_foreach_key(map,
					  apply_obj_config_map_for_key,
					  NULL);
}