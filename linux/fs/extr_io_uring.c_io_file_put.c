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
struct io_submit_state {int has_refs; int used_refs; int /*<<< orphan*/ * file; } ;

/* Variables and functions */
 int /*<<< orphan*/  fput_many (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void io_file_put(struct io_submit_state *state)
{
	if (state->file) {
		int diff = state->has_refs - state->used_refs;

		if (diff)
			fput_many(state->file, diff);
		state->file = NULL;
	}
}