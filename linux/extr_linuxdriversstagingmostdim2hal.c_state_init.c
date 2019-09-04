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
struct int_ch_state {scalar_t__ level; scalar_t__ idx2; scalar_t__ idx1; scalar_t__ service_counter; scalar_t__ request_counter; } ;

/* Variables and functions */

__attribute__((used)) static void state_init(struct int_ch_state *state)
{
	state->request_counter = 0;
	state->service_counter = 0;

	state->idx1 = 0;
	state->idx2 = 0;
	state->level = 0;
}