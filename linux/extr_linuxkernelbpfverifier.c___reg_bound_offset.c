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
struct bpf_reg_state {int /*<<< orphan*/  umax_value; int /*<<< orphan*/  umin_value; int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  tnum_intersect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tnum_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __reg_bound_offset(struct bpf_reg_state *reg)
{
	reg->var_off = tnum_intersect(reg->var_off,
				      tnum_range(reg->umin_value,
						 reg->umax_value));
}