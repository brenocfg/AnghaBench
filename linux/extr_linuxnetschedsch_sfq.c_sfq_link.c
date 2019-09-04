#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t next; size_t prev; } ;
struct sfq_slot {int qlen; TYPE_1__ dep; } ;
struct sfq_sched_data {TYPE_2__* dep; struct sfq_slot* slots; } ;
typedef  size_t sfq_index ;
struct TYPE_6__ {size_t prev; } ;
struct TYPE_5__ {size_t next; } ;

/* Variables and functions */
 size_t SFQ_MAX_FLOWS ; 
 TYPE_3__* sfq_dep_head (struct sfq_sched_data*,size_t) ; 

__attribute__((used)) static inline void sfq_link(struct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;
	struct sfq_slot *slot = &q->slots[x];
	int qlen = slot->qlen;

	p = qlen + SFQ_MAX_FLOWS;
	n = q->dep[qlen].next;

	slot->dep.next = n;
	slot->dep.prev = p;

	q->dep[qlen].next = x;		/* sfq_dep_head(q, p)->next = x */
	sfq_dep_head(q, n)->prev = x;
}