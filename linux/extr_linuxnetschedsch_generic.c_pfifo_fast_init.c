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
struct skb_array {int dummy; } ;
struct pfifo_fast_priv {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {unsigned int tx_queue_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PFIFO_FAST_BANDS ; 
 int /*<<< orphan*/  TCQ_F_CAN_BYPASS ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 TYPE_1__* qdisc_dev (struct Qdisc*) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 
 int skb_array_init (struct skb_array*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfifo_fast_init(struct Qdisc *qdisc, struct nlattr *opt,
			   struct netlink_ext_ack *extack)
{
	unsigned int qlen = qdisc_dev(qdisc)->tx_queue_len;
	struct pfifo_fast_priv *priv = qdisc_priv(qdisc);
	int prio;

	/* guard against zero length rings */
	if (!qlen)
		return -EINVAL;

	for (prio = 0; prio < PFIFO_FAST_BANDS; prio++) {
		struct skb_array *q = band2list(priv, prio);
		int err;

		err = skb_array_init(q, qlen, GFP_KERNEL);
		if (err)
			return -ENOMEM;
	}

	/* Can by-pass the queue discipline */
	qdisc->flags |= TCQ_F_CAN_BYPASS;
	return 0;
}