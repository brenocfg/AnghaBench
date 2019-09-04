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
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr_gen_mode; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 size_t IFLA_INET6_ADDR_GEN_MODE ; 
 int /*<<< orphan*/  IFLA_INET6_MAX ; 
 size_t IFLA_INET6_TOKEN ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 scalar_t__ check_addr_gen_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ check_stable_privacy (struct inet6_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int inet6_set_iftoken (struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inet6_set_link_af(struct net_device *dev, const struct nlattr *nla)
{
	int err = -EINVAL;
	struct inet6_dev *idev = __in6_dev_get(dev);
	struct nlattr *tb[IFLA_INET6_MAX + 1];

	if (!idev)
		return -EAFNOSUPPORT;

	if (nla_parse_nested(tb, IFLA_INET6_MAX, nla, NULL, NULL) < 0)
		BUG();

	if (tb[IFLA_INET6_TOKEN]) {
		err = inet6_set_iftoken(idev, nla_data(tb[IFLA_INET6_TOKEN]));
		if (err)
			return err;
	}

	if (tb[IFLA_INET6_ADDR_GEN_MODE]) {
		u8 mode = nla_get_u8(tb[IFLA_INET6_ADDR_GEN_MODE]);

		if (check_addr_gen_mode(mode) < 0 ||
		    check_stable_privacy(idev, dev_net(dev), mode) < 0)
			return -EINVAL;

		idev->cnf.addr_gen_mode = mode;
		err = 0;
	}

	return err;
}