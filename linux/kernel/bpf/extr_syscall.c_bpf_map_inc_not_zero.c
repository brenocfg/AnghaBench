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
 struct bpf_map* __bpf_map_inc_not_zero (struct bpf_map*,int) ; 
 int /*<<< orphan*/  map_idr_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct bpf_map *bpf_map_inc_not_zero(struct bpf_map *map, bool uref)
{
	spin_lock_bh(&map_idr_lock);
	map = __bpf_map_inc_not_zero(map, uref);
	spin_unlock_bh(&map_idr_lock);

	return map;
}