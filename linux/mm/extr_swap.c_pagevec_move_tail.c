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
 int /*<<< orphan*/  PGROTATED ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pagevec_lru_move_fn (struct pagevec*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pagevec_move_tail_fn ; 

__attribute__((used)) static void pagevec_move_tail(struct pagevec *pvec)
{
	int pgmoved = 0;

	pagevec_lru_move_fn(pvec, pagevec_move_tail_fn, &pgmoved);
	__count_vm_events(PGROTATED, pgmoved);
}