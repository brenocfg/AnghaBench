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
struct pagevec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNEVICTABLE_PGMUNLOCKED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGRESCUED ; 
 int /*<<< orphan*/  __pagevec_lru_add (struct pagevec*) ; 
 int /*<<< orphan*/  count_vm_events (int /*<<< orphan*/ ,int) ; 
 int pagevec_count (struct pagevec*) ; 

__attribute__((used)) static void __putback_lru_fast(struct pagevec *pvec, int pgrescued)
{
	count_vm_events(UNEVICTABLE_PGMUNLOCKED, pagevec_count(pvec));
	/*
	 *__pagevec_lru_add() calls release_pages() so we don't call
	 * put_page() explicitly
	 */
	__pagevec_lru_add(pvec);
	count_vm_events(UNEVICTABLE_PGRESCUED, pgrescued);
}