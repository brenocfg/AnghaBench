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
struct macsec_tx_sc {int /*<<< orphan*/ * sa; } ;
struct macsec_tx_sa {scalar_t__ active; } ;
struct macsec_secy {int dummy; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct macsec_tx_sa*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 int PTR_ERR (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_tx_sa (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct macsec_tx_sa* get_txsa_from_nl (int /*<<< orphan*/ ,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**,struct macsec_tx_sc**,size_t*) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int macsec_del_txsa(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr **attrs = info->attrs;
	struct net_device *dev;
	struct macsec_secy *secy;
	struct macsec_tx_sc *tx_sc;
	struct macsec_tx_sa *tx_sa;
	u8 assoc_num;
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	rtnl_lock();
	tx_sa = get_txsa_from_nl(genl_info_net(info), attrs, tb_sa,
				 &dev, &secy, &tx_sc, &assoc_num);
	if (IS_ERR(tx_sa)) {
		rtnl_unlock();
		return PTR_ERR(tx_sa);
	}

	if (tx_sa->active) {
		rtnl_unlock();
		return -EBUSY;
	}

	RCU_INIT_POINTER(tx_sc->sa[assoc_num], NULL);
	clear_tx_sa(tx_sa);

	rtnl_unlock();

	return 0;
}