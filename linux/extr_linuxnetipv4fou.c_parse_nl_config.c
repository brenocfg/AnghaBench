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
typedef  int u8 ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_2__ {int family; int ipv6_v6only; int /*<<< orphan*/  local_udp_port; } ;
struct fou_cfg {int /*<<< orphan*/  flags; void* type; void* protocol; TYPE_1__ udp_config; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAFNOSUPPORT ; 
 size_t FOU_ATTR_AF ; 
 size_t FOU_ATTR_IPPROTO ; 
 size_t FOU_ATTR_PORT ; 
 size_t FOU_ATTR_REMCSUM_NOPARTIAL ; 
 size_t FOU_ATTR_TYPE ; 
 int /*<<< orphan*/  FOU_F_REMCSUM_NOPARTIAL ; 
 int /*<<< orphan*/  memset (struct fou_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_be16 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 

__attribute__((used)) static int parse_nl_config(struct genl_info *info,
			   struct fou_cfg *cfg)
{
	memset(cfg, 0, sizeof(*cfg));

	cfg->udp_config.family = AF_INET;

	if (info->attrs[FOU_ATTR_AF]) {
		u8 family = nla_get_u8(info->attrs[FOU_ATTR_AF]);

		switch (family) {
		case AF_INET:
			break;
		case AF_INET6:
			cfg->udp_config.ipv6_v6only = 1;
			break;
		default:
			return -EAFNOSUPPORT;
		}

		cfg->udp_config.family = family;
	}

	if (info->attrs[FOU_ATTR_PORT]) {
		__be16 port = nla_get_be16(info->attrs[FOU_ATTR_PORT]);

		cfg->udp_config.local_udp_port = port;
	}

	if (info->attrs[FOU_ATTR_IPPROTO])
		cfg->protocol = nla_get_u8(info->attrs[FOU_ATTR_IPPROTO]);

	if (info->attrs[FOU_ATTR_TYPE])
		cfg->type = nla_get_u8(info->attrs[FOU_ATTR_TYPE]);

	if (info->attrs[FOU_ATTR_REMCSUM_NOPARTIAL])
		cfg->flags |= FOU_F_REMCSUM_NOPARTIAL;

	return 0;
}