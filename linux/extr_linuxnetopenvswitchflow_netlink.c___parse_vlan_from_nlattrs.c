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
typedef  int u64 ;
struct sw_flow_match {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int OVS_KEY_ATTR_ENCAP ; 
 int OVS_KEY_ATTR_ETHERTYPE ; 
 int OVS_KEY_ATTR_VLAN ; 
 int encode_vlan_from_nlattrs (struct sw_flow_match*,struct nlattr const**,int,int) ; 
 int parse_flow_mask_nlattrs (struct nlattr const*,struct nlattr const**,int*,int) ; 
 int parse_flow_nlattrs (struct nlattr const*,struct nlattr const**,int*,int) ; 
 int validate_vlan_from_nlattrs (struct sw_flow_match*,int,int,struct nlattr const**,int) ; 
 int validate_vlan_mask_from_nlattrs (struct sw_flow_match*,int,int,struct nlattr const**,int) ; 

__attribute__((used)) static int __parse_vlan_from_nlattrs(struct sw_flow_match *match,
				     u64 *key_attrs, bool inner,
				     const struct nlattr **a, bool is_mask,
				     bool log)
{
	int err;
	const struct nlattr *encap;

	if (!is_mask)
		err = validate_vlan_from_nlattrs(match, *key_attrs, inner,
						 a, log);
	else
		err = validate_vlan_mask_from_nlattrs(match, *key_attrs, inner,
						      a, log);
	if (err <= 0)
		return err;

	err = encode_vlan_from_nlattrs(match, a, is_mask, inner);
	if (err)
		return err;

	*key_attrs &= ~(1 << OVS_KEY_ATTR_ENCAP);
	*key_attrs &= ~(1 << OVS_KEY_ATTR_VLAN);
	*key_attrs &= ~(1 << OVS_KEY_ATTR_ETHERTYPE);

	encap = a[OVS_KEY_ATTR_ENCAP];

	if (!is_mask)
		err = parse_flow_nlattrs(encap, a, key_attrs, log);
	else
		err = parse_flow_mask_nlattrs(encap, a, key_attrs, log);

	return err;
}