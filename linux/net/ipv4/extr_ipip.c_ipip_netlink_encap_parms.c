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
struct nlattr {int dummy; } ;
struct ip_tunnel_encap {void* dport; void* sport; void* flags; void* type; } ;

/* Variables and functions */
 size_t IFLA_IPTUN_ENCAP_DPORT ; 
 size_t IFLA_IPTUN_ENCAP_FLAGS ; 
 size_t IFLA_IPTUN_ENCAP_SPORT ; 
 size_t IFLA_IPTUN_ENCAP_TYPE ; 
 int /*<<< orphan*/  memset (struct ip_tunnel_encap*,int /*<<< orphan*/ ,int) ; 
 void* nla_get_be16 (struct nlattr*) ; 
 void* nla_get_u16 (struct nlattr*) ; 

__attribute__((used)) static bool ipip_netlink_encap_parms(struct nlattr *data[],
				     struct ip_tunnel_encap *ipencap)
{
	bool ret = false;

	memset(ipencap, 0, sizeof(*ipencap));

	if (!data)
		return ret;

	if (data[IFLA_IPTUN_ENCAP_TYPE]) {
		ret = true;
		ipencap->type = nla_get_u16(data[IFLA_IPTUN_ENCAP_TYPE]);
	}

	if (data[IFLA_IPTUN_ENCAP_FLAGS]) {
		ret = true;
		ipencap->flags = nla_get_u16(data[IFLA_IPTUN_ENCAP_FLAGS]);
	}

	if (data[IFLA_IPTUN_ENCAP_SPORT]) {
		ret = true;
		ipencap->sport = nla_get_be16(data[IFLA_IPTUN_ENCAP_SPORT]);
	}

	if (data[IFLA_IPTUN_ENCAP_DPORT]) {
		ret = true;
		ipencap->dport = nla_get_be16(data[IFLA_IPTUN_ENCAP_DPORT]);
	}

	return ret;
}