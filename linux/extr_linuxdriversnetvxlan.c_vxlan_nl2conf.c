#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct vxlan_dev {int /*<<< orphan*/  cfg; } ;
struct TYPE_20__ {scalar_t__ sa_family; } ;
struct TYPE_19__ {void* sin6_addr; } ;
struct TYPE_17__ {void* s_addr; } ;
struct TYPE_18__ {TYPE_6__ sin_addr; } ;
struct TYPE_11__ {TYPE_9__ sa; TYPE_8__ sin6; TYPE_7__ sin; } ;
struct TYPE_15__ {scalar_t__ sa_family; } ;
struct TYPE_14__ {void* sin6_addr; } ;
struct TYPE_12__ {void* s_addr; } ;
struct TYPE_13__ {TYPE_1__ sin_addr; } ;
struct TYPE_16__ {TYPE_4__ sa; TYPE_3__ sin6; TYPE_2__ sin; } ;
struct vxlan_config {scalar_t__ vni; int label; void* mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  dst_port; void* port_max; void* port_min; void* addrmax; void* age_interval; void* ttl; void* tos; void* remote_ifindex; TYPE_10__ saddr; TYPE_5__ remote_ip; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct ifla_vxlan_port_range {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int EOPNOTSUPP ; 
 int EPFNOSUPPORT ; 
 size_t IFLA_MTU ; 
 size_t IFLA_VXLAN_AGEING ; 
 size_t IFLA_VXLAN_COLLECT_METADATA ; 
 size_t IFLA_VXLAN_GBP ; 
 size_t IFLA_VXLAN_GPE ; 
 size_t IFLA_VXLAN_GROUP ; 
 size_t IFLA_VXLAN_GROUP6 ; 
 size_t IFLA_VXLAN_ID ; 
 size_t IFLA_VXLAN_L2MISS ; 
 size_t IFLA_VXLAN_L3MISS ; 
 size_t IFLA_VXLAN_LABEL ; 
 size_t IFLA_VXLAN_LEARNING ; 
 size_t IFLA_VXLAN_LIMIT ; 
 size_t IFLA_VXLAN_LINK ; 
 size_t IFLA_VXLAN_LOCAL ; 
 size_t IFLA_VXLAN_LOCAL6 ; 
 size_t IFLA_VXLAN_PORT ; 
 size_t IFLA_VXLAN_PORT_RANGE ; 
 size_t IFLA_VXLAN_PROXY ; 
 size_t IFLA_VXLAN_REMCSUM_NOPARTIAL ; 
 size_t IFLA_VXLAN_REMCSUM_RX ; 
 size_t IFLA_VXLAN_REMCSUM_TX ; 
 size_t IFLA_VXLAN_RSC ; 
 size_t IFLA_VXLAN_TOS ; 
 size_t IFLA_VXLAN_TTL ; 
 size_t IFLA_VXLAN_TTL_INHERIT ; 
 size_t IFLA_VXLAN_UDP_CSUM ; 
 size_t IFLA_VXLAN_UDP_ZERO_CSUM6_RX ; 
 size_t IFLA_VXLAN_UDP_ZERO_CSUM6_TX ; 
 int IPV6_FLOWLABEL_MASK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXLAN_F_COLLECT_METADATA ; 
 int /*<<< orphan*/  VXLAN_F_GBP ; 
 int /*<<< orphan*/  VXLAN_F_GPE ; 
 int /*<<< orphan*/  VXLAN_F_L2MISS ; 
 int /*<<< orphan*/  VXLAN_F_L3MISS ; 
 int /*<<< orphan*/  VXLAN_F_LEARN ; 
 int /*<<< orphan*/  VXLAN_F_PROXY ; 
 int /*<<< orphan*/  VXLAN_F_REMCSUM_NOPARTIAL ; 
 int /*<<< orphan*/  VXLAN_F_REMCSUM_RX ; 
 int /*<<< orphan*/  VXLAN_F_REMCSUM_TX ; 
 int /*<<< orphan*/  VXLAN_F_RSC ; 
 int /*<<< orphan*/  VXLAN_F_TTL_INHERIT ; 
 int /*<<< orphan*/  VXLAN_F_UDP_ZERO_CSUM6_RX ; 
 int /*<<< orphan*/  VXLAN_F_UDP_ZERO_CSUM6_TX ; 
 int /*<<< orphan*/  VXLAN_F_UDP_ZERO_CSUM_TX ; 
 scalar_t__ cpu_to_be32 (void*) ; 
 int /*<<< orphan*/  memcpy (struct vxlan_config*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct vxlan_config*,int /*<<< orphan*/ ,int) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 struct ifla_vxlan_port_range* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int nla_get_be32 (struct nlattr*) ; 
 void* nla_get_in6_addr (struct nlattr*) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 void* nla_get_u32 (struct nlattr*) ; 
 void* nla_get_u8 (struct nlattr*) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_nl2conf(struct nlattr *tb[], struct nlattr *data[],
			 struct net_device *dev, struct vxlan_config *conf,
			 bool changelink)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);

	memset(conf, 0, sizeof(*conf));

	/* if changelink operation, start with old existing cfg */
	if (changelink)
		memcpy(conf, &vxlan->cfg, sizeof(*conf));

	if (data[IFLA_VXLAN_ID]) {
		__be32 vni = cpu_to_be32(nla_get_u32(data[IFLA_VXLAN_ID]));

		if (changelink && (vni != conf->vni))
			return -EOPNOTSUPP;
		conf->vni = cpu_to_be32(nla_get_u32(data[IFLA_VXLAN_ID]));
	}

	if (data[IFLA_VXLAN_GROUP]) {
		if (changelink && (conf->remote_ip.sa.sa_family != AF_INET))
			return -EOPNOTSUPP;

		conf->remote_ip.sin.sin_addr.s_addr = nla_get_in_addr(data[IFLA_VXLAN_GROUP]);
		conf->remote_ip.sa.sa_family = AF_INET;
	} else if (data[IFLA_VXLAN_GROUP6]) {
		if (!IS_ENABLED(CONFIG_IPV6))
			return -EPFNOSUPPORT;

		if (changelink && (conf->remote_ip.sa.sa_family != AF_INET6))
			return -EOPNOTSUPP;

		conf->remote_ip.sin6.sin6_addr = nla_get_in6_addr(data[IFLA_VXLAN_GROUP6]);
		conf->remote_ip.sa.sa_family = AF_INET6;
	}

	if (data[IFLA_VXLAN_LOCAL]) {
		if (changelink && (conf->saddr.sa.sa_family != AF_INET))
			return -EOPNOTSUPP;

		conf->saddr.sin.sin_addr.s_addr = nla_get_in_addr(data[IFLA_VXLAN_LOCAL]);
		conf->saddr.sa.sa_family = AF_INET;
	} else if (data[IFLA_VXLAN_LOCAL6]) {
		if (!IS_ENABLED(CONFIG_IPV6))
			return -EPFNOSUPPORT;

		if (changelink && (conf->saddr.sa.sa_family != AF_INET6))
			return -EOPNOTSUPP;

		/* TODO: respect scope id */
		conf->saddr.sin6.sin6_addr = nla_get_in6_addr(data[IFLA_VXLAN_LOCAL6]);
		conf->saddr.sa.sa_family = AF_INET6;
	}

	if (data[IFLA_VXLAN_LINK])
		conf->remote_ifindex = nla_get_u32(data[IFLA_VXLAN_LINK]);

	if (data[IFLA_VXLAN_TOS])
		conf->tos  = nla_get_u8(data[IFLA_VXLAN_TOS]);

	if (data[IFLA_VXLAN_TTL])
		conf->ttl = nla_get_u8(data[IFLA_VXLAN_TTL]);

	if (data[IFLA_VXLAN_TTL_INHERIT]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->flags |= VXLAN_F_TTL_INHERIT;
	}

	if (data[IFLA_VXLAN_LABEL])
		conf->label = nla_get_be32(data[IFLA_VXLAN_LABEL]) &
			     IPV6_FLOWLABEL_MASK;

	if (data[IFLA_VXLAN_LEARNING]) {
		if (nla_get_u8(data[IFLA_VXLAN_LEARNING]))
			conf->flags |= VXLAN_F_LEARN;
		else
			conf->flags &= ~VXLAN_F_LEARN;
	} else if (!changelink) {
		/* default to learn on a new device */
		conf->flags |= VXLAN_F_LEARN;
	}

	if (data[IFLA_VXLAN_AGEING]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->age_interval = nla_get_u32(data[IFLA_VXLAN_AGEING]);
	}

	if (data[IFLA_VXLAN_PROXY]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_PROXY]))
			conf->flags |= VXLAN_F_PROXY;
	}

	if (data[IFLA_VXLAN_RSC]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_RSC]))
			conf->flags |= VXLAN_F_RSC;
	}

	if (data[IFLA_VXLAN_L2MISS]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_L2MISS]))
			conf->flags |= VXLAN_F_L2MISS;
	}

	if (data[IFLA_VXLAN_L3MISS]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_L3MISS]))
			conf->flags |= VXLAN_F_L3MISS;
	}

	if (data[IFLA_VXLAN_LIMIT]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->addrmax = nla_get_u32(data[IFLA_VXLAN_LIMIT]);
	}

	if (data[IFLA_VXLAN_COLLECT_METADATA]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_COLLECT_METADATA]))
			conf->flags |= VXLAN_F_COLLECT_METADATA;
	}

	if (data[IFLA_VXLAN_PORT_RANGE]) {
		if (!changelink) {
			const struct ifla_vxlan_port_range *p
				= nla_data(data[IFLA_VXLAN_PORT_RANGE]);
			conf->port_min = ntohs(p->low);
			conf->port_max = ntohs(p->high);
		} else {
			return -EOPNOTSUPP;
		}
	}

	if (data[IFLA_VXLAN_PORT]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->dst_port = nla_get_be16(data[IFLA_VXLAN_PORT]);
	}

	if (data[IFLA_VXLAN_UDP_CSUM]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (!nla_get_u8(data[IFLA_VXLAN_UDP_CSUM]))
			conf->flags |= VXLAN_F_UDP_ZERO_CSUM_TX;
	}

	if (data[IFLA_VXLAN_UDP_ZERO_CSUM6_TX]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_UDP_ZERO_CSUM6_TX]))
			conf->flags |= VXLAN_F_UDP_ZERO_CSUM6_TX;
	}

	if (data[IFLA_VXLAN_UDP_ZERO_CSUM6_RX]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_UDP_ZERO_CSUM6_RX]))
			conf->flags |= VXLAN_F_UDP_ZERO_CSUM6_RX;
	}

	if (data[IFLA_VXLAN_REMCSUM_TX]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_REMCSUM_TX]))
			conf->flags |= VXLAN_F_REMCSUM_TX;
	}

	if (data[IFLA_VXLAN_REMCSUM_RX]) {
		if (changelink)
			return -EOPNOTSUPP;
		if (nla_get_u8(data[IFLA_VXLAN_REMCSUM_RX]))
			conf->flags |= VXLAN_F_REMCSUM_RX;
	}

	if (data[IFLA_VXLAN_GBP]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->flags |= VXLAN_F_GBP;
	}

	if (data[IFLA_VXLAN_GPE]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->flags |= VXLAN_F_GPE;
	}

	if (data[IFLA_VXLAN_REMCSUM_NOPARTIAL]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->flags |= VXLAN_F_REMCSUM_NOPARTIAL;
	}

	if (tb[IFLA_MTU]) {
		if (changelink)
			return -EOPNOTSUPP;
		conf->mtu = nla_get_u32(tb[IFLA_MTU]);
	}

	return 0;
}