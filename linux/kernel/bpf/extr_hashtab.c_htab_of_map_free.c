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
struct bpf_map {int /*<<< orphan*/  inner_map_meta; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_map_meta_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_htab_map_free (struct bpf_map*) ; 

__attribute__((used)) static void htab_of_map_free(struct bpf_map *map)
{
	bpf_map_meta_free(map->inner_map_meta);
	fd_htab_map_free(map);
}