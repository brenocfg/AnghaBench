#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sw_flow_match {TYPE_1__* key; scalar_t__ mask; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  tci; } ;
struct TYPE_6__ {int /*<<< orphan*/  tci; } ;
struct TYPE_8__ {TYPE_3__ cvlan; TYPE_2__ vlan; } ;
struct TYPE_5__ {scalar_t__ tun_proto; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_MAX ; 
 int /*<<< orphan*/  SW_FLOW_KEY_MEMSET_FIELD (struct sw_flow_match*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SW_FLOW_KEY_PUT (struct sw_flow_match*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ eth ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  kfree (struct nlattr*) ; 
 struct nlattr* kmemdup (struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_set_nlattr (struct nlattr*,int) ; 
 int /*<<< orphan*/  match_validate (struct sw_flow_match*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_total_size (int /*<<< orphan*/ ) ; 
 int ovs_key_from_nlattrs (struct net*,struct sw_flow_match*,int /*<<< orphan*/ ,struct nlattr const**,int,int) ; 
 int parse_flow_mask_nlattrs (struct nlattr const*,struct nlattr const**,int /*<<< orphan*/ *,int) ; 
 int parse_flow_nlattrs (struct nlattr const*,struct nlattr const**,int /*<<< orphan*/ *,int) ; 
 int parse_vlan_from_nlattrs (struct sw_flow_match*,int /*<<< orphan*/ *,struct nlattr const**,int,int) ; 
 int /*<<< orphan*/  tun_key ; 

int ovs_nla_get_match(struct net *net, struct sw_flow_match *match,
		      const struct nlattr *nla_key,
		      const struct nlattr *nla_mask,
		      bool log)
{
	const struct nlattr *a[OVS_KEY_ATTR_MAX + 1];
	struct nlattr *newmask = NULL;
	u64 key_attrs = 0;
	u64 mask_attrs = 0;
	int err;

	err = parse_flow_nlattrs(nla_key, a, &key_attrs, log);
	if (err)
		return err;

	err = parse_vlan_from_nlattrs(match, &key_attrs, a, false, log);
	if (err)
		return err;

	err = ovs_key_from_nlattrs(net, match, key_attrs, a, false, log);
	if (err)
		return err;

	if (match->mask) {
		if (!nla_mask) {
			/* Create an exact match mask. We need to set to 0xff
			 * all the 'match->mask' fields that have been touched
			 * in 'match->key'. We cannot simply memset
			 * 'match->mask', because padding bytes and fields not
			 * specified in 'match->key' should be left to 0.
			 * Instead, we use a stream of netlink attributes,
			 * copied from 'key' and set to 0xff.
			 * ovs_key_from_nlattrs() will take care of filling
			 * 'match->mask' appropriately.
			 */
			newmask = kmemdup(nla_key,
					  nla_total_size(nla_len(nla_key)),
					  GFP_KERNEL);
			if (!newmask)
				return -ENOMEM;

			mask_set_nlattr(newmask, 0xff);

			/* The userspace does not send tunnel attributes that
			 * are 0, but we should not wildcard them nonetheless.
			 */
			if (match->key->tun_proto)
				SW_FLOW_KEY_MEMSET_FIELD(match, tun_key,
							 0xff, true);

			nla_mask = newmask;
		}

		err = parse_flow_mask_nlattrs(nla_mask, a, &mask_attrs, log);
		if (err)
			goto free_newmask;

		/* Always match on tci. */
		SW_FLOW_KEY_PUT(match, eth.vlan.tci, htons(0xffff), true);
		SW_FLOW_KEY_PUT(match, eth.cvlan.tci, htons(0xffff), true);

		err = parse_vlan_from_nlattrs(match, &mask_attrs, a, true, log);
		if (err)
			goto free_newmask;

		err = ovs_key_from_nlattrs(net, match, mask_attrs, a, true,
					   log);
		if (err)
			goto free_newmask;
	}

	if (!match_validate(match, key_attrs, mask_attrs, log))
		err = -EINVAL;

free_newmask:
	kfree(newmask);
	return err;
}