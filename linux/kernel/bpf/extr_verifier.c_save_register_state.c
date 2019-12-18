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
struct bpf_reg_state {int /*<<< orphan*/  live; } ;
struct bpf_func_state {TYPE_1__* stack; } ;
struct TYPE_2__ {int /*<<< orphan*/ * slot_type; struct bpf_reg_state spilled_ptr; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int /*<<< orphan*/  REG_LIVE_WRITTEN ; 
 int /*<<< orphan*/  STACK_SPILL ; 

__attribute__((used)) static void save_register_state(struct bpf_func_state *state,
				int spi, struct bpf_reg_state *reg)
{
	int i;

	state->stack[spi].spilled_ptr = *reg;
	state->stack[spi].spilled_ptr.live |= REG_LIVE_WRITTEN;

	for (i = 0; i < BPF_REG_SIZE; i++)
		state->stack[spi].slot_type[i] = STACK_SPILL;
}