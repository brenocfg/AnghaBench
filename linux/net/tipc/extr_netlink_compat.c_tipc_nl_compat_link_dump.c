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
struct tipc_link_info {int /*<<< orphan*/  str; int /*<<< orphan*/  up; int /*<<< orphan*/  dest; } ;
struct nlattr {int dummy; } ;
typedef  int /*<<< orphan*/  link_info ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TIPC_MAX_LINK_NAME ; 
 size_t TIPC_NLA_LINK ; 
 size_t TIPC_NLA_LINK_DEST ; 
 int /*<<< orphan*/  TIPC_NLA_LINK_MAX ; 
 size_t TIPC_NLA_LINK_NAME ; 
 size_t TIPC_NLA_LINK_UP ; 
 int /*<<< orphan*/  TIPC_TLV_LINK_INFO ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_flag (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nla_strlcpy (int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int tipc_add_tlv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_link_info*,int) ; 

__attribute__((used)) static int tipc_nl_compat_link_dump(struct tipc_nl_compat_msg *msg,
				    struct nlattr **attrs)
{
	struct nlattr *link[TIPC_NLA_LINK_MAX + 1];
	struct tipc_link_info link_info;
	int err;

	if (!attrs[TIPC_NLA_LINK])
		return -EINVAL;

	err = nla_parse_nested_deprecated(link, TIPC_NLA_LINK_MAX,
					  attrs[TIPC_NLA_LINK], NULL, NULL);
	if (err)
		return err;

	link_info.dest = nla_get_flag(link[TIPC_NLA_LINK_DEST]);
	link_info.up = htonl(nla_get_flag(link[TIPC_NLA_LINK_UP]));
	nla_strlcpy(link_info.str, link[TIPC_NLA_LINK_NAME],
		    TIPC_MAX_LINK_NAME);

	return tipc_add_tlv(msg->rep, TIPC_TLV_LINK_INFO,
			    &link_info, sizeof(link_info));
}