#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct per_cpu_dm_data {int /*<<< orphan*/  lock; TYPE_2__ send_timer; struct sk_buff* skb; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int /*<<< orphan*/  nla_len; } ;
struct net_dm_drop_point {int dummy; } ;
struct net_dm_alert_msg {int entries; TYPE_1__* points; } ;
struct TYPE_4__ {int count; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ NLA_ALIGN (int) ; 
 int /*<<< orphan*/  __nla_reserve_nohdr (struct sk_buff*,int) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  dm_cpu_data ; 
 int dm_delay ; 
 int dm_hit_limit ; 
 struct nlattr* genlmsg_data (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memcmp (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 
 struct net_dm_alert_msg* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct per_cpu_dm_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 

__attribute__((used)) static void trace_drop_common(struct sk_buff *skb, void *location)
{
	struct net_dm_alert_msg *msg;
	struct nlmsghdr *nlh;
	struct nlattr *nla;
	int i;
	struct sk_buff *dskb;
	struct per_cpu_dm_data *data;
	unsigned long flags;

	local_irq_save(flags);
	data = this_cpu_ptr(&dm_cpu_data);
	spin_lock(&data->lock);
	dskb = data->skb;

	if (!dskb)
		goto out;

	nlh = (struct nlmsghdr *)dskb->data;
	nla = genlmsg_data(nlmsg_data(nlh));
	msg = nla_data(nla);
	for (i = 0; i < msg->entries; i++) {
		if (!memcmp(&location, msg->points[i].pc, sizeof(void *))) {
			msg->points[i].count++;
			goto out;
		}
	}
	if (msg->entries == dm_hit_limit)
		goto out;
	/*
	 * We need to create a new entry
	 */
	__nla_reserve_nohdr(dskb, sizeof(struct net_dm_drop_point));
	nla->nla_len += NLA_ALIGN(sizeof(struct net_dm_drop_point));
	memcpy(msg->points[msg->entries].pc, &location, sizeof(void *));
	msg->points[msg->entries].count = 1;
	msg->entries++;

	if (!timer_pending(&data->send_timer)) {
		data->send_timer.expires = jiffies + dm_delay * HZ;
		add_timer(&data->send_timer);
	}

out:
	spin_unlock_irqrestore(&data->lock, flags);
}