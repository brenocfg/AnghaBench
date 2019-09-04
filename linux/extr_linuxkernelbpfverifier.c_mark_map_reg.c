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
typedef  size_t u32 ;
struct bpf_reg_state {scalar_t__ type; size_t id; TYPE_1__* map_ptr; scalar_t__ off; int /*<<< orphan*/  var_off; scalar_t__ smax_value; scalar_t__ smin_value; } ;
struct TYPE_2__ {struct TYPE_2__* inner_map_meta; } ;

/* Variables and functions */
 scalar_t__ CONST_PTR_TO_MAP ; 
 scalar_t__ PTR_TO_MAP_VALUE ; 
 scalar_t__ PTR_TO_MAP_VALUE_OR_NULL ; 
 scalar_t__ SCALAR_VALUE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __mark_reg_known_zero (struct bpf_reg_state*) ; 
 int /*<<< orphan*/  tnum_equals_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_map_reg(struct bpf_reg_state *regs, u32 regno, u32 id,
			 bool is_null)
{
	struct bpf_reg_state *reg = &regs[regno];

	if (reg->type == PTR_TO_MAP_VALUE_OR_NULL && reg->id == id) {
		/* Old offset (both fixed and variable parts) should
		 * have been known-zero, because we don't allow pointer
		 * arithmetic on pointers that might be NULL.
		 */
		if (WARN_ON_ONCE(reg->smin_value || reg->smax_value ||
				 !tnum_equals_const(reg->var_off, 0) ||
				 reg->off)) {
			__mark_reg_known_zero(reg);
			reg->off = 0;
		}
		if (is_null) {
			reg->type = SCALAR_VALUE;
		} else if (reg->map_ptr->inner_map_meta) {
			reg->type = CONST_PTR_TO_MAP;
			reg->map_ptr = reg->map_ptr->inner_map_meta;
		} else {
			reg->type = PTR_TO_MAP_VALUE;
		}
		/* We don't need id from this point onwards anymore, thus we
		 * should better reset it, so that state pruning has chances
		 * to take effect.
		 */
		reg->id = 0;
	}
}