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
struct TYPE_2__ {scalar_t__ lockdep_depth; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  print_held_locks_bug () ; 
 scalar_t__ unlikely (int) ; 

void debug_check_no_locks_held(void)
{
	if (unlikely(current->lockdep_depth > 0))
		print_held_locks_bug();
}