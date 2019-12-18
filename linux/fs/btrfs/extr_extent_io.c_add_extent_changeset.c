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
struct extent_state {unsigned int state; scalar_t__ end; scalar_t__ start; } ;
struct extent_changeset {int /*<<< orphan*/  range_changed; int /*<<< orphan*/  bytes_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ulist_add (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_extent_changeset(struct extent_state *state, unsigned bits,
				 struct extent_changeset *changeset,
				 int set)
{
	int ret;

	if (!changeset)
		return 0;
	if (set && (state->state & bits) == bits)
		return 0;
	if (!set && (state->state & bits) == 0)
		return 0;
	changeset->bytes_changed += state->end - state->start + 1;
	ret = ulist_add(&changeset->range_changed, state->start, state->end,
			GFP_ATOMIC);
	return ret;
}