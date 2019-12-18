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
struct xsk_map {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_map_put (int /*<<< orphan*/ *) ; 

void xsk_map_put(struct xsk_map *map)
{
	bpf_map_put(&map->map);
}