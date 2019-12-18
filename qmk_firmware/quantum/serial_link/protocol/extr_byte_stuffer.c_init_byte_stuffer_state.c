#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int long_frame; scalar_t__ data_pos; scalar_t__ next_zero; } ;
typedef  TYPE_1__ byte_stuffer_state_t ;

/* Variables and functions */

void init_byte_stuffer_state(byte_stuffer_state_t* state) {
    state->next_zero  = 0;
    state->data_pos   = 0;
    state->long_frame = false;
}