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
struct TYPE_2__ {int (* nlattr_to_obj ) (struct nlattr**,struct net*,void*) ;int /*<<< orphan*/  nla_policy; int /*<<< orphan*/  nlattr_max; } ;
struct nf_conntrack_l4proto {TYPE_1__ ctnl_timeout; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nlattr** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nlattr**) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct nlattr**,struct net*,void*) ; 

__attribute__((used)) static int
ctnl_timeout_parse_policy(void *timeout,
			  const struct nf_conntrack_l4proto *l4proto,
			  struct net *net, const struct nlattr *attr)
{
	struct nlattr **tb;
	int ret = 0;

	tb = kcalloc(l4proto->ctnl_timeout.nlattr_max + 1, sizeof(*tb),
		     GFP_KERNEL);

	if (!tb)
		return -ENOMEM;

	ret = nla_parse_nested_deprecated(tb,
					  l4proto->ctnl_timeout.nlattr_max,
					  attr,
					  l4proto->ctnl_timeout.nla_policy,
					  NULL);
	if (ret < 0)
		goto err;

	ret = l4proto->ctnl_timeout.nlattr_to_obj(tb, net, timeout);

err:
	kfree(tb);
	return ret;
}