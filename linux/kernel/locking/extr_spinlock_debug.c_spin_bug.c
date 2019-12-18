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
typedef  int /*<<< orphan*/  raw_spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  spin_dump (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void spin_bug(raw_spinlock_t *lock, const char *msg)
{
	if (!debug_locks_off())
		return;

	spin_dump(lock, msg);
}