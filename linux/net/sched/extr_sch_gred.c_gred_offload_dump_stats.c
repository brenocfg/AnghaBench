#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* qstats; TYPE_2__* bstats; int /*<<< orphan*/ ** xstats; } ;
struct tc_gred_qopt_offload {TYPE_5__ stats; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; int /*<<< orphan*/  command; } ;
struct gred_sched {TYPE_1__** tab; } ;
struct TYPE_8__ {int /*<<< orphan*/  overlimits; int /*<<< orphan*/  requeues; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog; int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_3__ qstats; int /*<<< orphan*/  bstats; int /*<<< orphan*/  parent; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {scalar_t__ overlimits; scalar_t__ requeues; scalar_t__ drops; scalar_t__ backlog; scalar_t__ qlen; } ;
struct TYPE_7__ {scalar_t__ packets; scalar_t__ bytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  backlog; int /*<<< orphan*/  bytesin; int /*<<< orphan*/  packetsin; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_DPs ; 
 int /*<<< orphan*/  TC_GRED_STATS ; 
 int /*<<< orphan*/  TC_SETUP_QDISC_GRED ; 
 int /*<<< orphan*/  _bstats_update (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct tc_gred_qopt_offload*) ; 
 struct tc_gred_qopt_offload* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qdisc_offload_dump_helper (struct Qdisc*,int /*<<< orphan*/ ,struct tc_gred_qopt_offload*) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int gred_offload_dump_stats(struct Qdisc *sch)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct tc_gred_qopt_offload *hw_stats;
	unsigned int i;
	int ret;

	hw_stats = kzalloc(sizeof(*hw_stats), GFP_KERNEL);
	if (!hw_stats)
		return -ENOMEM;

	hw_stats->command = TC_GRED_STATS;
	hw_stats->handle = sch->handle;
	hw_stats->parent = sch->parent;

	for (i = 0; i < MAX_DPs; i++)
		if (table->tab[i])
			hw_stats->stats.xstats[i] = &table->tab[i]->stats;

	ret = qdisc_offload_dump_helper(sch, TC_SETUP_QDISC_GRED, hw_stats);
	/* Even if driver returns failure adjust the stats - in case offload
	 * ended but driver still wants to adjust the values.
	 */
	for (i = 0; i < MAX_DPs; i++) {
		if (!table->tab[i])
			continue;
		table->tab[i]->packetsin += hw_stats->stats.bstats[i].packets;
		table->tab[i]->bytesin += hw_stats->stats.bstats[i].bytes;
		table->tab[i]->backlog += hw_stats->stats.qstats[i].backlog;

		_bstats_update(&sch->bstats,
			       hw_stats->stats.bstats[i].bytes,
			       hw_stats->stats.bstats[i].packets);
		sch->qstats.qlen += hw_stats->stats.qstats[i].qlen;
		sch->qstats.backlog += hw_stats->stats.qstats[i].backlog;
		sch->qstats.drops += hw_stats->stats.qstats[i].drops;
		sch->qstats.requeues += hw_stats->stats.qstats[i].requeues;
		sch->qstats.overlimits += hw_stats->stats.qstats[i].overlimits;
	}

	kfree(hw_stats);
	return ret;
}