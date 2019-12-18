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
struct tcf_ematch {int datalen; unsigned long data; } ;
struct net {int dummy; } ;
struct canid_match {int rules_count; scalar_t__ sff_rules_count; scalar_t__ eff_rules_count; scalar_t__ rules_raw; } ;
struct can_filter {int can_id; int /*<<< orphan*/  can_mask; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int EINVAL ; 
 int EM_CAN_RULES_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  em_canid_sff_match_add (struct canid_match*,int,int /*<<< orphan*/ ) ; 
 struct canid_match* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct can_filter*,int) ; 

__attribute__((used)) static int em_canid_change(struct net *net, void *data, int len,
			  struct tcf_ematch *m)
{
	struct can_filter *conf = data; /* Array with rules */
	struct canid_match *cm;
	int i;

	if (!len)
		return -EINVAL;

	if (len % sizeof(struct can_filter))
		return -EINVAL;

	if (len > sizeof(struct can_filter) * EM_CAN_RULES_MAX)
		return -EINVAL;

	cm = kzalloc(sizeof(struct canid_match) + len, GFP_KERNEL);
	if (!cm)
		return -ENOMEM;

	cm->rules_count = len / sizeof(struct can_filter);

	/*
	 * We need two for() loops for copying rules into two contiguous
	 * areas in rules_raw to process all eff rules with a simple loop.
	 * NB: The configuration interface supports sff and eff rules.
	 * We do not support filters here that match for the same can_id
	 * provided in a SFF and EFF frame (e.g. 0x123 / 0x80000123).
	 * For this (unusual case) two filters have to be specified. The
	 * SFF/EFF separation is done with the CAN_EFF_FLAG in the can_id.
	 */

	/* Fill rules_raw with EFF rules first */
	for (i = 0; i < cm->rules_count; i++) {
		if (conf[i].can_id & CAN_EFF_FLAG) {
			memcpy(cm->rules_raw + cm->eff_rules_count,
				&conf[i],
				sizeof(struct can_filter));

			cm->eff_rules_count++;
		}
	}

	/* append SFF frame rules */
	for (i = 0; i < cm->rules_count; i++) {
		if (!(conf[i].can_id & CAN_EFF_FLAG)) {
			memcpy(cm->rules_raw
				+ cm->eff_rules_count
				+ cm->sff_rules_count,
				&conf[i], sizeof(struct can_filter));

			cm->sff_rules_count++;

			em_canid_sff_match_add(cm,
				conf[i].can_id, conf[i].can_mask);
		}
	}

	m->datalen = sizeof(struct canid_match) + len;
	m->data = (unsigned long)cm;
	return 0;
}