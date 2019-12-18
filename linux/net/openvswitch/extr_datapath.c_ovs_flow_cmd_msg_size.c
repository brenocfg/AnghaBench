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
typedef  int /*<<< orphan*/  uint32_t ;
struct sw_flow_id {int ufid_len; } ;
struct sw_flow_actions {int orig_len; } ;
struct ovs_header {int dummy; } ;
struct ovs_flow_stats {int dummy; } ;

/* Variables and functions */
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 
 scalar_t__ ovs_identifier_is_ufid (struct sw_flow_id const*) ; 
 int ovs_key_attr_size () ; 
 scalar_t__ should_fill_actions (int /*<<< orphan*/ ) ; 
 scalar_t__ should_fill_key (struct sw_flow_id const*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_fill_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ovs_flow_cmd_msg_size(const struct sw_flow_actions *acts,
				    const struct sw_flow_id *sfid,
				    uint32_t ufid_flags)
{
	size_t len = NLMSG_ALIGN(sizeof(struct ovs_header));

	/* OVS_FLOW_ATTR_UFID */
	if (sfid && ovs_identifier_is_ufid(sfid))
		len += nla_total_size(sfid->ufid_len);

	/* OVS_FLOW_ATTR_KEY */
	if (!sfid || should_fill_key(sfid, ufid_flags))
		len += nla_total_size(ovs_key_attr_size());

	/* OVS_FLOW_ATTR_MASK */
	if (should_fill_mask(ufid_flags))
		len += nla_total_size(ovs_key_attr_size());

	/* OVS_FLOW_ATTR_ACTIONS */
	if (should_fill_actions(ufid_flags))
		len += nla_total_size(acts->orig_len);

	return len
		+ nla_total_size_64bit(sizeof(struct ovs_flow_stats)) /* OVS_FLOW_ATTR_STATS */
		+ nla_total_size(1) /* OVS_FLOW_ATTR_TCP_FLAGS */
		+ nla_total_size_64bit(8); /* OVS_FLOW_ATTR_USED */
}