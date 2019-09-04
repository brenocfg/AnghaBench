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
struct mm_struct {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void verify_mm_writelocked(struct mm_struct *mm)
{
#ifdef CONFIG_DEBUG_VM
	if (unlikely(down_read_trylock(&mm->mmap_sem))) {
		WARN_ON(1);
		up_read(&mm->mmap_sem);
	}
#endif
}