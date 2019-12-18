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
struct wined3d_context {unsigned int* dirty_compute_states; TYPE_1__* state_table; } ;
struct TYPE_2__ {size_t representative; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 int CHAR_BIT ; 
 size_t STATE_COMPUTE_OFFSET ; 

void context_invalidate_compute_state(struct wined3d_context *context, DWORD state_id)
{
    DWORD representative = context->state_table[state_id].representative - STATE_COMPUTE_OFFSET;
    unsigned int index, shift;

    index = representative / (sizeof(*context->dirty_compute_states) * CHAR_BIT);
    shift = representative & (sizeof(*context->dirty_compute_states) * CHAR_BIT - 1);
    context->dirty_compute_states[index] |= (1u << shift);
}