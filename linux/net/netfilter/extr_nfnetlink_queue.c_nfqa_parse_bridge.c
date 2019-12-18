#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nlattr {int dummy; } ;
struct nf_queue_entry {TYPE_1__* skb; } ;
struct TYPE_3__ {int network_header; int mac_header; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFQA_L2HDR ; 
 size_t NFQA_VLAN ; 
 int /*<<< orphan*/  NFQA_VLAN_MAX ; 
 size_t NFQA_VLAN_PROTO ; 
 size_t NFQA_VLAN_TCI ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfqa_vlan_policy ; 
 int /*<<< orphan*/  nla_data (struct nlattr const* const) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int nla_len (struct nlattr const* const) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mac_header (TYPE_1__*) ; 

__attribute__((used)) static int nfqa_parse_bridge(struct nf_queue_entry *entry,
			     const struct nlattr * const nfqa[])
{
	if (nfqa[NFQA_VLAN]) {
		struct nlattr *tb[NFQA_VLAN_MAX + 1];
		int err;

		err = nla_parse_nested_deprecated(tb, NFQA_VLAN_MAX,
						  nfqa[NFQA_VLAN],
						  nfqa_vlan_policy, NULL);
		if (err < 0)
			return err;

		if (!tb[NFQA_VLAN_TCI] || !tb[NFQA_VLAN_PROTO])
			return -EINVAL;

		__vlan_hwaccel_put_tag(entry->skb,
			nla_get_be16(tb[NFQA_VLAN_PROTO]),
			ntohs(nla_get_be16(tb[NFQA_VLAN_TCI])));
	}

	if (nfqa[NFQA_L2HDR]) {
		int mac_header_len = entry->skb->network_header -
			entry->skb->mac_header;

		if (mac_header_len != nla_len(nfqa[NFQA_L2HDR]))
			return -EINVAL;
		else if (mac_header_len > 0)
			memcpy(skb_mac_header(entry->skb),
			       nla_data(nfqa[NFQA_L2HDR]),
			       mac_header_len);
	}

	return 0;
}