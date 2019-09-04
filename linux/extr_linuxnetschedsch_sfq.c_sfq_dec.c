#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sfq_sched_data {int cur_depth; TYPE_1__* slots; } ;
typedef  size_t sfq_index ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfq_link (struct sfq_sched_data*,size_t) ; 
 int /*<<< orphan*/  sfq_unlink (struct sfq_sched_data*,size_t,size_t,size_t) ; 

__attribute__((used)) static inline void sfq_dec(struct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;
	int d;

	sfq_unlink(q, x, n, p);

	d = q->slots[x].qlen--;
	if (n == p && q->cur_depth == d)
		q->cur_depth--;
	sfq_link(q, x);
}