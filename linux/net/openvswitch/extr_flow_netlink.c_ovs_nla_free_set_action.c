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
struct ovs_tunnel_info {scalar_t__ tun_dst; } ;
struct nlattr {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
#define  OVS_KEY_ATTR_TUNNEL_INFO 128 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 void* nla_data (struct nlattr const*) ; 
 int nla_type (struct nlattr const*) ; 

__attribute__((used)) static void ovs_nla_free_set_action(const struct nlattr *a)
{
	const struct nlattr *ovs_key = nla_data(a);
	struct ovs_tunnel_info *ovs_tun;

	switch (nla_type(ovs_key)) {
	case OVS_KEY_ATTR_TUNNEL_INFO:
		ovs_tun = nla_data(ovs_key);
		dst_release((struct dst_entry *)ovs_tun->tun_dst);
		break;
	}
}