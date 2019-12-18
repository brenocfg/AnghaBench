#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fq_flow {int dummy; } ;
struct codel_vars {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vif; } ;
struct txq_info {struct fq_flow def_flow; struct codel_vars def_cvars; TYPE_1__ txq; } ;
struct sk_buff {int dummy; } ;
struct fq {struct fq_flow* flows; } ;
struct ieee80211_local {struct codel_vars* cvars; struct fq fq; } ;
struct TYPE_4__ {struct ieee80211_local* local; } ;

/* Variables and functions */
 struct sk_buff* fq_flow_dequeue (struct fq*,struct fq_flow*) ; 
 TYPE_2__* vif_to_sdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *codel_dequeue_func(struct codel_vars *cvars,
					  void *ctx)
{
	struct ieee80211_local *local;
	struct txq_info *txqi;
	struct fq *fq;
	struct fq_flow *flow;

	txqi = ctx;
	local = vif_to_sdata(txqi->txq.vif)->local;
	fq = &local->fq;

	if (cvars == &txqi->def_cvars)
		flow = &txqi->def_flow;
	else
		flow = &fq->flows[cvars - local->cvars];

	return fq_flow_dequeue(fq, flow);
}