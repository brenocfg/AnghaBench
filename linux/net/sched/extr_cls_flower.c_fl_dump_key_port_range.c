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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct fl_flow_key {TYPE_2__ tp_max; TYPE_1__ tp_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_FLOWER_KEY_PORT_DST_MAX ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_PORT_DST_MIN ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_PORT_SRC_MAX ; 
 int /*<<< orphan*/  TCA_FLOWER_KEY_PORT_SRC_MIN ; 
 int /*<<< orphan*/  TCA_FLOWER_UNSPEC ; 
 scalar_t__ fl_dump_key_val (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fl_dump_key_port_range(struct sk_buff *skb, struct fl_flow_key *key,
				  struct fl_flow_key *mask)
{
	if (fl_dump_key_val(skb, &key->tp_min.dst, TCA_FLOWER_KEY_PORT_DST_MIN,
			    &mask->tp_min.dst, TCA_FLOWER_UNSPEC,
			    sizeof(key->tp_min.dst)) ||
	    fl_dump_key_val(skb, &key->tp_max.dst, TCA_FLOWER_KEY_PORT_DST_MAX,
			    &mask->tp_max.dst, TCA_FLOWER_UNSPEC,
			    sizeof(key->tp_max.dst)) ||
	    fl_dump_key_val(skb, &key->tp_min.src, TCA_FLOWER_KEY_PORT_SRC_MIN,
			    &mask->tp_min.src, TCA_FLOWER_UNSPEC,
			    sizeof(key->tp_min.src)) ||
	    fl_dump_key_val(skb, &key->tp_max.src, TCA_FLOWER_KEY_PORT_SRC_MAX,
			    &mask->tp_max.src, TCA_FLOWER_UNSPEC,
			    sizeof(key->tp_max.src)))
		return -1;

	return 0;
}