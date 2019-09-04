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
struct sfb_sched_data {int /*<<< orphan*/  increment; } ;
struct sfb_bucket {int /*<<< orphan*/  p_mark; } ;

/* Variables and functions */
 int /*<<< orphan*/  prob_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void increment_prob(struct sfb_bucket *b, struct sfb_sched_data *q)
{
	b->p_mark = prob_plus(b->p_mark, q->increment);
}