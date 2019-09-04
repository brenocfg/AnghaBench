#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_state {struct bpf_verifier_state* parent; TYPE_3__** frame; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_6__ {int allocated_stack; TYPE_2__* stack; } ;
struct TYPE_4__ {int live; } ;
struct TYPE_5__ {TYPE_1__ spilled_ptr; } ;

/* Variables and functions */
 int BPF_REG_SIZE ; 
 int REG_LIVE_READ ; 
 int REG_LIVE_WRITTEN ; 

__attribute__((used)) static void mark_stack_slot_read(struct bpf_verifier_env *env,
				 const struct bpf_verifier_state *state,
				 struct bpf_verifier_state *parent,
				 int slot, int frameno)
{
	bool writes = parent == state->parent; /* Observe write marks */

	while (parent) {
		if (parent->frame[frameno]->allocated_stack <= slot * BPF_REG_SIZE)
			/* since LIVE_WRITTEN mark is only done for full 8-byte
			 * write the read marks are conservative and parent
			 * state may not even have the stack allocated. In such case
			 * end the propagation, since the loop reached beginning
			 * of the function
			 */
			break;
		/* if read wasn't screened by an earlier write ... */
		if (writes && state->frame[frameno]->stack[slot].spilled_ptr.live & REG_LIVE_WRITTEN)
			break;
		/* ... then we depend on parent's value */
		parent->frame[frameno]->stack[slot].spilled_ptr.live |= REG_LIVE_READ;
		state = parent;
		parent = state->parent;
		writes = true;
	}
}