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
typedef  scalar_t__ u32 ;
struct sched_entry {scalar_t__ interval; void* gate_mask; int /*<<< orphan*/  command; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_TAPRIO_SCHED_ENTRY_CMD ; 
 size_t TCA_TAPRIO_SCHED_ENTRY_GATE_MASK ; 
 size_t TCA_TAPRIO_SCHED_ENTRY_INTERVAL ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 

__attribute__((used)) static int fill_sched_entry(struct nlattr **tb, struct sched_entry *entry,
			    struct netlink_ext_ack *extack)
{
	u32 interval = 0;

	if (tb[TCA_TAPRIO_SCHED_ENTRY_CMD])
		entry->command = nla_get_u8(
			tb[TCA_TAPRIO_SCHED_ENTRY_CMD]);

	if (tb[TCA_TAPRIO_SCHED_ENTRY_GATE_MASK])
		entry->gate_mask = nla_get_u32(
			tb[TCA_TAPRIO_SCHED_ENTRY_GATE_MASK]);

	if (tb[TCA_TAPRIO_SCHED_ENTRY_INTERVAL])
		interval = nla_get_u32(
			tb[TCA_TAPRIO_SCHED_ENTRY_INTERVAL]);

	if (interval == 0) {
		NL_SET_ERR_MSG(extack, "Invalid interval for schedule entry");
		return -EINVAL;
	}

	entry->interval = interval;

	return 0;
}