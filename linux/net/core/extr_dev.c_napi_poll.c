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
struct napi_struct {int weight; int (* poll ) (struct napi_struct*,int) ;int /*<<< orphan*/  poll_list; TYPE_1__* dev; scalar_t__ gro_bitmask; int /*<<< orphan*/  state; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NAPI_STATE_SCHED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  gro_normal_list (struct napi_struct*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 int napi_disable_pending (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_gro_flush (struct napi_struct*,int) ; 
 void* netpoll_poll_lock (struct napi_struct*) ; 
 int /*<<< orphan*/  netpoll_poll_unlock (void*) ; 
 int /*<<< orphan*/  pr_warn_once (char*,char*) ; 
 int stub1 (struct napi_struct*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_napi_poll (struct napi_struct*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int napi_poll(struct napi_struct *n, struct list_head *repoll)
{
	void *have;
	int work, weight;

	list_del_init(&n->poll_list);

	have = netpoll_poll_lock(n);

	weight = n->weight;

	/* This NAPI_STATE_SCHED test is for avoiding a race
	 * with netpoll's poll_napi().  Only the entity which
	 * obtains the lock and sees NAPI_STATE_SCHED set will
	 * actually make the ->poll() call.  Therefore we avoid
	 * accidentally calling ->poll() when NAPI is not scheduled.
	 */
	work = 0;
	if (test_bit(NAPI_STATE_SCHED, &n->state)) {
		work = n->poll(n, weight);
		trace_napi_poll(n, work, weight);
	}

	WARN_ON_ONCE(work > weight);

	if (likely(work < weight))
		goto out_unlock;

	/* Drivers must not modify the NAPI state if they
	 * consume the entire weight.  In such cases this code
	 * still "owns" the NAPI instance and therefore can
	 * move the instance around on the list at-will.
	 */
	if (unlikely(napi_disable_pending(n))) {
		napi_complete(n);
		goto out_unlock;
	}

	gro_normal_list(n);

	if (n->gro_bitmask) {
		/* flush too old packets
		 * If HZ < 1000, flush all packets.
		 */
		napi_gro_flush(n, HZ >= 1000);
	}

	/* Some drivers may have called napi_schedule
	 * prior to exhausting their budget.
	 */
	if (unlikely(!list_empty(&n->poll_list))) {
		pr_warn_once("%s: Budget exhausted after napi rescheduled\n",
			     n->dev ? n->dev->name : "backlog");
		goto out_unlock;
	}

	list_add_tail(&n->poll_list, repoll);

out_unlock:
	netpoll_poll_unlock(have);

	return work;
}