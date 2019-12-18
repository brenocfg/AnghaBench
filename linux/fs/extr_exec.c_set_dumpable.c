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
 int /*<<< orphan*/  MMF_DUMPABLE_MASK ; 
 unsigned int SUID_DUMP_ROOT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  set_mask_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void set_dumpable(struct mm_struct *mm, int value)
{
	if (WARN_ON((unsigned)value > SUID_DUMP_ROOT))
		return;

	set_mask_bits(&mm->flags, MMF_DUMPABLE_MASK, value);
}