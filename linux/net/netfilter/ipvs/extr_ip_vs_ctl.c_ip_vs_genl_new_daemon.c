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
struct nlattr {int dummy; } ;
struct netns_ipvs {scalar_t__ mixed_address_family_dests; } ;
struct TYPE_2__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  ip; } ;
struct ipvs_sync_daemon_cfg {int /*<<< orphan*/  mcast_ttl; void* mcast_port; TYPE_1__ mcast_group; int /*<<< orphan*/  mcast_af; void* sync_maxlen; int /*<<< orphan*/  syncid; int /*<<< orphan*/  mcast_ifn; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int IPV6_ADDR_MULTICAST ; 
 size_t IPVS_DAEMON_ATTR_MCAST_GROUP ; 
 size_t IPVS_DAEMON_ATTR_MCAST_GROUP6 ; 
 size_t IPVS_DAEMON_ATTR_MCAST_IFN ; 
 size_t IPVS_DAEMON_ATTR_MCAST_PORT ; 
 size_t IPVS_DAEMON_ATTR_MCAST_TTL ; 
 size_t IPVS_DAEMON_ATTR_STATE ; 
 size_t IPVS_DAEMON_ATTR_SYNC_ID ; 
 size_t IPVS_DAEMON_ATTR_SYNC_MAXLEN ; 
 int /*<<< orphan*/  ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ipvs_sync_daemon_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_in6_addr (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_in_addr (struct nlattr*) ; 
 void* nla_get_u16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int start_sync_thread (struct netns_ipvs*,struct ipvs_sync_daemon_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip_vs_genl_new_daemon(struct netns_ipvs *ipvs, struct nlattr **attrs)
{
	struct ipvs_sync_daemon_cfg c;
	struct nlattr *a;
	int ret;

	memset(&c, 0, sizeof(c));
	if (!(attrs[IPVS_DAEMON_ATTR_STATE] &&
	      attrs[IPVS_DAEMON_ATTR_MCAST_IFN] &&
	      attrs[IPVS_DAEMON_ATTR_SYNC_ID]))
		return -EINVAL;
	strlcpy(c.mcast_ifn, nla_data(attrs[IPVS_DAEMON_ATTR_MCAST_IFN]),
		sizeof(c.mcast_ifn));
	c.syncid = nla_get_u32(attrs[IPVS_DAEMON_ATTR_SYNC_ID]);

	a = attrs[IPVS_DAEMON_ATTR_SYNC_MAXLEN];
	if (a)
		c.sync_maxlen = nla_get_u16(a);

	a = attrs[IPVS_DAEMON_ATTR_MCAST_GROUP];
	if (a) {
		c.mcast_af = AF_INET;
		c.mcast_group.ip = nla_get_in_addr(a);
		if (!ipv4_is_multicast(c.mcast_group.ip))
			return -EINVAL;
	} else {
		a = attrs[IPVS_DAEMON_ATTR_MCAST_GROUP6];
		if (a) {
#ifdef CONFIG_IP_VS_IPV6
			int addr_type;

			c.mcast_af = AF_INET6;
			c.mcast_group.in6 = nla_get_in6_addr(a);
			addr_type = ipv6_addr_type(&c.mcast_group.in6);
			if (!(addr_type & IPV6_ADDR_MULTICAST))
				return -EINVAL;
#else
			return -EAFNOSUPPORT;
#endif
		}
	}

	a = attrs[IPVS_DAEMON_ATTR_MCAST_PORT];
	if (a)
		c.mcast_port = nla_get_u16(a);

	a = attrs[IPVS_DAEMON_ATTR_MCAST_TTL];
	if (a)
		c.mcast_ttl = nla_get_u8(a);

	/* The synchronization protocol is incompatible with mixed family
	 * services
	 */
	if (ipvs->mixed_address_family_dests > 0)
		return -EINVAL;

	ret = start_sync_thread(ipvs, &c,
				nla_get_u32(attrs[IPVS_DAEMON_ATTR_STATE]));
	return ret;
}