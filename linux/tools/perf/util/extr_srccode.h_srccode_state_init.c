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
struct srccode_state {scalar_t__ line; int /*<<< orphan*/ * srcfile; } ;

/* Variables and functions */

__attribute__((used)) static inline void srccode_state_init(struct srccode_state *state)
{
	state->srcfile = NULL;
	state->line    = 0;
}