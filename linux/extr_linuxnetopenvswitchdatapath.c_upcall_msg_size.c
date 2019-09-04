#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ovs_header {int dummy; } ;
struct dp_upcall_info {scalar_t__ mru; scalar_t__ actions_len; scalar_t__ egress_tun_info; TYPE_1__* userdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  nla_len; } ;

/* Variables and functions */
 scalar_t__ NLA_ALIGN (int /*<<< orphan*/ ) ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 
 int ovs_key_attr_size () ; 
 int ovs_tun_key_attr_size () ; 

__attribute__((used)) static size_t upcall_msg_size(const struct dp_upcall_info *upcall_info,
			      unsigned int hdrlen, int actions_attrlen)
{
	size_t size = NLMSG_ALIGN(sizeof(struct ovs_header))
		+ nla_total_size(hdrlen) /* OVS_PACKET_ATTR_PACKET */
		+ nla_total_size(ovs_key_attr_size()) /* OVS_PACKET_ATTR_KEY */
		+ nla_total_size(sizeof(unsigned int)); /* OVS_PACKET_ATTR_LEN */

	/* OVS_PACKET_ATTR_USERDATA */
	if (upcall_info->userdata)
		size += NLA_ALIGN(upcall_info->userdata->nla_len);

	/* OVS_PACKET_ATTR_EGRESS_TUN_KEY */
	if (upcall_info->egress_tun_info)
		size += nla_total_size(ovs_tun_key_attr_size());

	/* OVS_PACKET_ATTR_ACTIONS */
	if (upcall_info->actions_len)
		size += nla_total_size(actions_attrlen);

	/* OVS_PACKET_ATTR_MRU */
	if (upcall_info->mru)
		size += nla_total_size(sizeof(upcall_info->mru));

	return size;
}