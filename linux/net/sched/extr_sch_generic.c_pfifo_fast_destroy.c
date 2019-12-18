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
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;
struct skb_array {TYPE_1__ ring; } ;
struct pfifo_fast_priv {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int PFIFO_FAST_BANDS ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 int /*<<< orphan*/  ptr_ring_cleanup (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void pfifo_fast_destroy(struct Qdisc *sch)
{
	struct pfifo_fast_priv *priv = qdisc_priv(sch);
	int prio;

	for (prio = 0; prio < PFIFO_FAST_BANDS; prio++) {
		struct skb_array *q = band2list(priv, prio);

		/* NULL ring is possible if destroy path is due to a failed
		 * skb_array_init() in pfifo_fast_init() case.
		 */
		if (!q->ring.queue)
			continue;
		/* Destroy ring but no need to kfree_skb because a call to
		 * pfifo_fast_reset() has already done that work.
		 */
		ptr_ring_cleanup(&q->ring, NULL);
	}
}