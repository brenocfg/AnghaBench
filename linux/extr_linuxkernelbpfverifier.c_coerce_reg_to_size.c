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
typedef  int u64 ;
struct bpf_reg_state {int umin_value; int umax_value; int smin_value; int smax_value; int /*<<< orphan*/  var_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  tnum_cast (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void coerce_reg_to_size(struct bpf_reg_state *reg, int size)
{
	u64 mask;

	/* clear high bits in bit representation */
	reg->var_off = tnum_cast(reg->var_off, size);

	/* fix arithmetic bounds */
	mask = ((u64)1 << (size * 8)) - 1;
	if ((reg->umin_value & ~mask) == (reg->umax_value & ~mask)) {
		reg->umin_value &= mask;
		reg->umax_value &= mask;
	} else {
		reg->umin_value = 0;
		reg->umax_value = mask;
	}
	reg->smin_value = reg->umin_value;
	reg->smax_value = reg->umax_value;
}