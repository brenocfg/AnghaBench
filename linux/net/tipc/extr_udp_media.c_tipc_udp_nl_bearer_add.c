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
struct udp_media_addr {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct tipc_bearer {TYPE_1__ bcast_addr; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_NLA_UDP_MAX ; 
 size_t TIPC_NLA_UDP_REMOTE ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tipc_nl_udp_policy ; 
 int tipc_parse_udp_addr (struct nlattr*,struct udp_media_addr*,int /*<<< orphan*/ *) ; 
 scalar_t__ tipc_udp_is_known_peer (struct tipc_bearer*,struct udp_media_addr*) ; 
 scalar_t__ tipc_udp_is_mcast_addr (struct udp_media_addr*) ; 
 int tipc_udp_rcast_add (struct tipc_bearer*,struct udp_media_addr*) ; 

int tipc_udp_nl_bearer_add(struct tipc_bearer *b, struct nlattr *attr)
{
	int err;
	struct udp_media_addr addr = {0};
	struct nlattr *opts[TIPC_NLA_UDP_MAX + 1];
	struct udp_media_addr *dst;

	if (nla_parse_nested_deprecated(opts, TIPC_NLA_UDP_MAX, attr, tipc_nl_udp_policy, NULL))
		return -EINVAL;

	if (!opts[TIPC_NLA_UDP_REMOTE])
		return -EINVAL;

	err = tipc_parse_udp_addr(opts[TIPC_NLA_UDP_REMOTE], &addr, NULL);
	if (err)
		return err;

	dst = (struct udp_media_addr *)&b->bcast_addr.value;
	if (tipc_udp_is_mcast_addr(dst)) {
		pr_err("Can't add remote ip to TIPC UDP multicast bearer\n");
		return -EINVAL;
	}

	if (tipc_udp_is_known_peer(b, &addr))
		return 0;

	return tipc_udp_rcast_add(b, &addr);
}