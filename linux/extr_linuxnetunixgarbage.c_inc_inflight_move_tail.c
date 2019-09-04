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
struct unix_sock {int /*<<< orphan*/  link; int /*<<< orphan*/  gc_flags; int /*<<< orphan*/  inflight; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIX_GC_MAYBE_CYCLE ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_candidates ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inc_inflight_move_tail(struct unix_sock *u)
{
	atomic_long_inc(&u->inflight);
	/* If this still might be part of a cycle, move it to the end
	 * of the list, so that it's checked even if it was already
	 * passed over
	 */
	if (test_bit(UNIX_GC_MAYBE_CYCLE, &u->gc_flags))
		list_move_tail(&u->link, &gc_candidates);
}