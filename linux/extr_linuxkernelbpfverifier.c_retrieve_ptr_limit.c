#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ value; } ;
struct bpf_reg_state {int type; TYPE_2__* map_ptr; scalar_t__ off; scalar_t__ smin_value; scalar_t__ umax_value; TYPE_1__ var_off; } ;
struct TYPE_4__ {scalar_t__ value_size; } ;

/* Variables and functions */
 scalar_t__ BPF_ADD ; 
 scalar_t__ BPF_SUB ; 
 int EINVAL ; 
 scalar_t__ MAX_BPF_STACK ; 
#define  PTR_TO_MAP_VALUE 129 
#define  PTR_TO_STACK 128 

__attribute__((used)) static int retrieve_ptr_limit(const struct bpf_reg_state *ptr_reg,
			      u32 *ptr_limit, u8 opcode, bool off_is_neg)
{
	bool mask_to_left = (opcode == BPF_ADD &&  off_is_neg) ||
			    (opcode == BPF_SUB && !off_is_neg);
	u32 off;

	switch (ptr_reg->type) {
	case PTR_TO_STACK:
		off = ptr_reg->off + ptr_reg->var_off.value;
		if (mask_to_left)
			*ptr_limit = MAX_BPF_STACK + off;
		else
			*ptr_limit = -off;
		return 0;
	case PTR_TO_MAP_VALUE:
		if (mask_to_left) {
			*ptr_limit = ptr_reg->umax_value + ptr_reg->off;
		} else {
			off = ptr_reg->smin_value + ptr_reg->off;
			*ptr_limit = ptr_reg->map_ptr->value_size - off;
		}
		return 0;
	default:
		return -EINVAL;
	}
}