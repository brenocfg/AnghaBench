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
struct nlattr {void* value; void* mask; } ;
struct nfacct_filter {void* value; void* mask; } ;
struct netlink_callback {struct nlattr* data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NFACCT_FILTER_MASK ; 
 int /*<<< orphan*/  NFACCT_FILTER_MAX ; 
 size_t NFACCT_FILTER_VALUE ; 
 int /*<<< orphan*/  filter_policy ; 
 struct nlattr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfnl_acct_start(struct netlink_callback *cb)
{
	const struct nlattr *const attr = cb->data;
	struct nlattr *tb[NFACCT_FILTER_MAX + 1];
	struct nfacct_filter *filter;
	int err;

	if (!attr)
		return 0;

	err = nla_parse_nested_deprecated(tb, NFACCT_FILTER_MAX, attr,
					  filter_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[NFACCT_FILTER_MASK] || !tb[NFACCT_FILTER_VALUE])
		return -EINVAL;

	filter = kzalloc(sizeof(struct nfacct_filter), GFP_KERNEL);
	if (!filter)
		return -ENOMEM;

	filter->mask = ntohl(nla_get_be32(tb[NFACCT_FILTER_MASK]));
	filter->value = ntohl(nla_get_be32(tb[NFACCT_FILTER_VALUE]));
	cb->data = filter;

	return 0;
}