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

/* Variables and functions */
 int EINVAL ; 
 size_t TIPC_NLA_MEDIA ; 
 int /*<<< orphan*/  TIPC_NLA_MEDIA_MAX ; 
 size_t TIPC_NLA_MEDIA_NAME ; 
 int /*<<< orphan*/  TIPC_TLV_MEDIA_NAME ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tipc_add_tlv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_nl_compat_media_dump(struct tipc_nl_compat_msg *msg,
				     struct nlattr **attrs)
{
	struct nlattr *media[TIPC_NLA_MEDIA_MAX + 1];
	int err;

	if (!attrs[TIPC_NLA_MEDIA])
		return -EINVAL;

	err = nla_parse_nested_deprecated(media, TIPC_NLA_MEDIA_MAX,
					  attrs[TIPC_NLA_MEDIA], NULL, NULL);
	if (err)
		return err;

	return tipc_add_tlv(msg->rep, TIPC_TLV_MEDIA_NAME,
			    nla_data(media[TIPC_NLA_MEDIA_NAME]),
			    nla_len(media[TIPC_NLA_MEDIA_NAME]));
}