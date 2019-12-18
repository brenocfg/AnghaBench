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
struct tc_plug_qopt {int action; int /*<<< orphan*/  limit; } ;
struct plug_sched_data {int unplug_indefinite; int throttled; int /*<<< orphan*/  limit; int /*<<< orphan*/  pkts_current_epoch; int /*<<< orphan*/  pkts_last_epoch; int /*<<< orphan*/  pkts_to_release; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TCQ_PLUG_BUFFER 131 
#define  TCQ_PLUG_LIMIT 130 
#define  TCQ_PLUG_RELEASE_INDEFINITE 129 
#define  TCQ_PLUG_RELEASE_ONE 128 
 int /*<<< orphan*/  netif_schedule_queue (int /*<<< orphan*/ ) ; 
 struct tc_plug_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct plug_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int plug_change(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct plug_sched_data *q = qdisc_priv(sch);
	struct tc_plug_qopt *msg;

	if (opt == NULL)
		return -EINVAL;

	msg = nla_data(opt);
	if (nla_len(opt) < sizeof(*msg))
		return -EINVAL;

	switch (msg->action) {
	case TCQ_PLUG_BUFFER:
		/* Save size of the current buffer */
		q->pkts_last_epoch = q->pkts_current_epoch;
		q->pkts_current_epoch = 0;
		if (q->unplug_indefinite)
			q->throttled = true;
		q->unplug_indefinite = false;
		break;
	case TCQ_PLUG_RELEASE_ONE:
		/* Add packets from the last complete buffer to the
		 * packets to be released set.
		 */
		q->pkts_to_release += q->pkts_last_epoch;
		q->pkts_last_epoch = 0;
		q->throttled = false;
		netif_schedule_queue(sch->dev_queue);
		break;
	case TCQ_PLUG_RELEASE_INDEFINITE:
		q->unplug_indefinite = true;
		q->pkts_to_release = 0;
		q->pkts_last_epoch = 0;
		q->pkts_current_epoch = 0;
		q->throttled = false;
		netif_schedule_queue(sch->dev_queue);
		break;
	case TCQ_PLUG_LIMIT:
		/* Limit is supplied in bytes */
		q->limit = msg->limit;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}