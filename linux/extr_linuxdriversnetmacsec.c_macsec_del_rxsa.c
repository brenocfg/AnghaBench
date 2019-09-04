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
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macsec_secy {int dummy; } ;
struct macsec_rx_sc {int /*<<< orphan*/ * sa; } ;
struct macsec_rx_sa {scalar_t__ active; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct macsec_rx_sa*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 int /*<<< orphan*/  MACSEC_RXSC_ATTR_MAX ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 int PTR_ERR (struct macsec_rx_sa*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_rx_sa (struct macsec_rx_sa*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct macsec_rx_sa* get_rxsa_from_nl (int /*<<< orphan*/ ,struct nlattr**,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**,struct macsec_rx_sc**,size_t*) ; 
 scalar_t__ parse_rxsc_config (struct nlattr**,struct nlattr**) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int macsec_del_rxsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct net_device *dev;
	struct macsec_secy *secy;
	struct macsec_rx_sc *rx_sc;
	struct macsec_rx_sa *rx_sa;
	u8 assoc_num;
	struct nlattr *tb_rxsc[MACSEC_RXSC_ATTR_MAX + 1];
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (parse_rxsc_config(attrs, tb_rxsc))
		return -EINVAL;

	rtnl_lock();
	rx_sa = get_rxsa_from_nl(genl_info_net(info), attrs, tb_rxsc, tb_sa,
				 &dev, &secy, &rx_sc, &assoc_num);
	if (IS_ERR(rx_sa)) {
		rtnl_unlock();
		return PTR_ERR(rx_sa);
	}

	if (rx_sa->active) {
		rtnl_unlock();
		return -EBUSY;
	}

	RCU_INIT_POINTER(rx_sc->sa[assoc_num], NULL);
	clear_rx_sa(rx_sa);

	rtnl_unlock();

	return 0;
}