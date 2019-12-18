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
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMUNLOCKED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGSTRANDED ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __munlock_isolation_failed(struct page *page)
{
	if (PageUnevictable(page))
		__count_vm_event(UNEVICTABLE_PGSTRANDED);
	else
		__count_vm_event(UNEVICTABLE_PGMUNLOCKED);
}