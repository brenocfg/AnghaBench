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
struct TYPE_2__ {int value; int mask; } ;
struct bpf_reg_state {TYPE_1__ var_off; int /*<<< orphan*/  umax_value; int /*<<< orphan*/  umin_value; int /*<<< orphan*/  smax_value; int /*<<< orphan*/  smin_value; } ;

/* Variables and functions */
 int S64_MAX ; 
 int S64_MIN ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s64 ; 

__attribute__((used)) static void __update_reg_bounds(struct bpf_reg_state *reg)
{
	/* min signed is max(sign bit) | min(other bits) */
	reg->smin_value = max_t(s64, reg->smin_value,
				reg->var_off.value | (reg->var_off.mask & S64_MIN));
	/* max signed is min(sign bit) | max(other bits) */
	reg->smax_value = min_t(s64, reg->smax_value,
				reg->var_off.value | (reg->var_off.mask & S64_MAX));
	reg->umin_value = max(reg->umin_value, reg->var_off.value);
	reg->umax_value = min(reg->umax_value,
			      reg->var_off.value | reg->var_off.mask);
}