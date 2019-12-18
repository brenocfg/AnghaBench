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
struct bpf_reg_state {scalar_t__ type; int /*<<< orphan*/  map_ptr; } ;

/* Variables and functions */
 scalar_t__ PTR_TO_MAP_VALUE ; 
 scalar_t__ map_value_has_spin_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reg_may_point_to_spin_lock(const struct bpf_reg_state *reg)
{
	return reg->type == PTR_TO_MAP_VALUE &&
		map_value_has_spin_lock(reg->map_ptr);
}