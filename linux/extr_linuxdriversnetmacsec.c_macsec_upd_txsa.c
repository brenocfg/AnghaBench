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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macsec_tx_sc {scalar_t__ encoding_sa; } ;
struct macsec_tx_sa {int /*<<< orphan*/  active; int /*<<< orphan*/  lock; int /*<<< orphan*/  next_pn; } ;
struct macsec_secy {int /*<<< orphan*/  operational; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct macsec_tx_sa*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 size_t MACSEC_SA_ATTR_ACTIVE ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_PN ; 
 int PTR_ERR (struct macsec_tx_sa*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct macsec_tx_sa* get_txsa_from_nl (int /*<<< orphan*/ ,struct nlattr**,struct nlattr**,struct net_device**,struct macsec_secy**,struct macsec_tx_sc**,scalar_t__*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_upd_sa (struct nlattr**) ; 

__attribute__((used)) static int macsec_upd_txsa(struct sk_buff *skb, struct genl_info *info)
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

	if (!validate_upd_sa(tb_sa))
		return -EINVAL;

	rtnl_lock();
	tx_sa = get_txsa_from_nl(genl_info_net(info), attrs, tb_sa,
				 &dev, &secy, &tx_sc, &assoc_num);
	if (IS_ERR(tx_sa)) {
		rtnl_unlock();
		return PTR_ERR(tx_sa);
	}

	if (tb_sa[MACSEC_SA_ATTR_PN]) {
		spin_lock_bh(&tx_sa->lock);
		tx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);
		spin_unlock_bh(&tx_sa->lock);
	}

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		tx_sa->active = nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	if (assoc_num == tx_sc->encoding_sa)
		secy->operational = tx_sa->active;

	rtnl_unlock();

	return 0;
}