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
struct sfb_sched_data {int slot; int double_buffering; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfb_init_perturbation (int,struct sfb_sched_data*) ; 

__attribute__((used)) static void sfb_swap_slot(struct sfb_sched_data *q)
{
	sfb_init_perturbation(q->slot, q);
	q->slot ^= 1;
	q->double_buffering = false;
}