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
struct tipc_nl_compat_msg {int /*<<< orphan*/  rep; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 size_t TIPC_NLA_NET ; 
 size_t TIPC_NLA_NET_ID ; 
 int /*<<< orphan*/  TIPC_NLA_NET_MAX ; 
 int /*<<< orphan*/  TIPC_TLV_UNSIGNED ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tipc_add_tlv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tipc_nl_compat_net_dump(struct tipc_nl_compat_msg *msg,
				   struct nlattr **attrs)
{
	__be32 id;
	struct nlattr *net[TIPC_NLA_NET_MAX + 1];
	int err;

	if (!attrs[TIPC_NLA_NET])
		return -EINVAL;

	err = nla_parse_nested_deprecated(net, TIPC_NLA_NET_MAX,
					  attrs[TIPC_NLA_NET], NULL, NULL);
	if (err)
		return err;

	id = htonl(nla_get_u32(net[TIPC_NLA_NET_ID]));

	return tipc_add_tlv(msg->rep, TIPC_TLV_UNSIGNED, &id, sizeof(id));
}