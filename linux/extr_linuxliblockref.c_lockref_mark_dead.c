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
struct lockref {int count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

void lockref_mark_dead(struct lockref *lockref)
{
	assert_spin_locked(&lockref->lock);
	lockref->count = -128;
}