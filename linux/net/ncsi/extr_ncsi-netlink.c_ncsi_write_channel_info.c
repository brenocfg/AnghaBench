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
struct nlattr {int dummy; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel_vlan_filter {int n_vids; scalar_t__* vids; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel_mode {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_name; int /*<<< orphan*/  alpha2; int /*<<< orphan*/  version; } ;
struct ncsi_channel {scalar_t__ state; struct ncsi_channel_vlan_filter vlan_filter; TYPE_2__ version; TYPE_1__* package; struct ncsi_channel_mode* modes; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct ncsi_channel* preferred_channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ NCSI_CHANNEL_ACTIVE ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_ACTIVE ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_FORCED ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_ID ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_LINK_STATE ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_VERSION_MAJOR ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_VERSION_MINOR ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_VERSION_STR ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_VLAN_ID ; 
 int /*<<< orphan*/  NCSI_CHANNEL_ATTR_VLAN_LIST ; 
 size_t NCSI_MODE_LINK ; 
 int find_next_bit (void*,int,int) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ncsi_write_channel_info(struct sk_buff *skb,
				   struct ncsi_dev_priv *ndp,
				   struct ncsi_channel *nc)
{
	struct ncsi_channel_vlan_filter *ncf;
	struct ncsi_channel_mode *m;
	struct nlattr *vid_nest;
	int i;

	nla_put_u32(skb, NCSI_CHANNEL_ATTR_ID, nc->id);
	m = &nc->modes[NCSI_MODE_LINK];
	nla_put_u32(skb, NCSI_CHANNEL_ATTR_LINK_STATE, m->data[2]);
	if (nc->state == NCSI_CHANNEL_ACTIVE)
		nla_put_flag(skb, NCSI_CHANNEL_ATTR_ACTIVE);
	if (nc == nc->package->preferred_channel)
		nla_put_flag(skb, NCSI_CHANNEL_ATTR_FORCED);

	nla_put_u32(skb, NCSI_CHANNEL_ATTR_VERSION_MAJOR, nc->version.version);
	nla_put_u32(skb, NCSI_CHANNEL_ATTR_VERSION_MINOR, nc->version.alpha2);
	nla_put_string(skb, NCSI_CHANNEL_ATTR_VERSION_STR, nc->version.fw_name);

	vid_nest = nla_nest_start_noflag(skb, NCSI_CHANNEL_ATTR_VLAN_LIST);
	if (!vid_nest)
		return -ENOMEM;
	ncf = &nc->vlan_filter;
	i = -1;
	while ((i = find_next_bit((void *)&ncf->bitmap, ncf->n_vids,
				  i + 1)) < ncf->n_vids) {
		if (ncf->vids[i])
			nla_put_u16(skb, NCSI_CHANNEL_ATTR_VLAN_ID,
				    ncf->vids[i]);
	}
	nla_nest_end(skb, vid_nest);

	return 0;
}