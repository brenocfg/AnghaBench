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
typedef  int /*<<< orphan*/  xstats ;
struct tc_sfq_xstats {int allot; int /*<<< orphan*/  member_0; } ;
struct sfq_slot {int allot; int /*<<< orphan*/  backlog; int /*<<< orphan*/  qlen; } ;
struct sfq_sched_data {size_t* ht; struct sfq_slot* slots; } ;
struct gnet_stats_queue {int /*<<< orphan*/  qlen; int /*<<< orphan*/  backlog; int /*<<< orphan*/  member_0; } ;
struct gnet_dump {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  size_t sfq_index ;

/* Variables and functions */
 int SFQ_ALLOT_SHIFT ; 
 size_t SFQ_EMPTY_SLOT ; 
 int gnet_stats_copy_app (struct gnet_dump*,struct tc_sfq_xstats*,int) ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,struct gnet_stats_queue*,int /*<<< orphan*/ ) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int sfq_dump_class_stats(struct Qdisc *sch, unsigned long cl,
				struct gnet_dump *d)
{
	struct sfq_sched_data *q = qdisc_priv(sch);
	sfq_index idx = q->ht[cl - 1];
	struct gnet_stats_queue qs = { 0 };
	struct tc_sfq_xstats xstats = { 0 };

	if (idx != SFQ_EMPTY_SLOT) {
		const struct sfq_slot *slot = &q->slots[idx];

		xstats.allot = slot->allot << SFQ_ALLOT_SHIFT;
		qs.qlen = slot->qlen;
		qs.backlog = slot->backlog;
	}
	if (gnet_stats_copy_queue(d, NULL, &qs, qs.qlen) < 0)
		return -1;
	return gnet_stats_copy_app(d, &xstats, sizeof(xstats));
}