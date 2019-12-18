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
struct lockdep_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_data_structures_once () ; 
 scalar_t__ inside_selftest () ; 
 int /*<<< orphan*/  lockdep_reset_lock_imm (struct lockdep_map*) ; 
 int /*<<< orphan*/  lockdep_reset_lock_reg (struct lockdep_map*) ; 

void lockdep_reset_lock(struct lockdep_map *lock)
{
	init_data_structures_once();

	if (inside_selftest())
		lockdep_reset_lock_imm(lock);
	else
		lockdep_reset_lock_reg(lock);
}