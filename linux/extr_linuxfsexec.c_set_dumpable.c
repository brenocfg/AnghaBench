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
struct mm_struct {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned long MMF_DUMPABLE_MASK ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int SUID_DUMP_ROOT ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 

void set_dumpable(struct mm_struct *mm, int value)
{
	unsigned long old, new;

	if (WARN_ON((unsigned)value > SUID_DUMP_ROOT))
		return;

	do {
		old = READ_ONCE(mm->flags);
		new = (old & ~MMF_DUMPABLE_MASK) | value;
	} while (cmpxchg(&mm->flags, old, new) != old);
}