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
struct xsk_map {struct bpf_map map; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (struct bpf_map*) ; 
 struct bpf_map* bpf_map_inc (struct bpf_map*,int) ; 

int xsk_map_inc(struct xsk_map *map)
{
	struct bpf_map *m = &map->map;

	m = bpf_map_inc(m, false);
	return PTR_ERR_OR_ZERO(m);
}