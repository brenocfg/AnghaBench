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
struct choke_sched_data {size_t tail; int tab_mask; int head; int /*<<< orphan*/ ** tab; } ;

/* Variables and functions */

__attribute__((used)) static void choke_zap_tail_holes(struct choke_sched_data *q)
{
	do {
		q->tail = (q->tail - 1) & q->tab_mask;
		if (q->head == q->tail)
			break;
	} while (q->tab[q->tail] == NULL);
}