#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int dummy; } ;
struct macsec_tx_sc {unsigned char encoding_sa; int /*<<< orphan*/ * sa; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct macsec_tx_sa {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  next_pn; TYPE_1__ key; } ;
struct macsec_secy {scalar_t__ key_len; int operational; int /*<<< orphan*/  icv_len; struct macsec_tx_sc tx_sc; } ;
struct genl_info {struct nlattr** attrs; } ;
struct TYPE_4__ {struct macsec_secy secy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct net_device*) ; 
 size_t MACSEC_ATTR_IFINDEX ; 
 int /*<<< orphan*/  MACSEC_KEYID_LEN ; 
 size_t MACSEC_SA_ATTR_ACTIVE ; 
 size_t MACSEC_SA_ATTR_AN ; 
 size_t MACSEC_SA_ATTR_KEY ; 
 size_t MACSEC_SA_ATTR_KEYID ; 
 int /*<<< orphan*/  MACSEC_SA_ATTR_MAX ; 
 size_t MACSEC_SA_ATTR_PN ; 
 int PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct net_device* get_dev_from_nl (int /*<<< orphan*/ ,struct nlattr**) ; 
 int init_tx_sa (struct macsec_tx_sa*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct macsec_tx_sa*) ; 
 struct macsec_tx_sa* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* macsec_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 unsigned char nla_get_u8 (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_sa_config (struct nlattr**,struct nlattr**) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct macsec_tx_sa*) ; 
 struct macsec_tx_sa* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_add_txsa (struct nlattr**) ; 

__attribute__((used)) static int macsec_add_txsa(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device *dev;
	struct nlattr **attrs = info->attrs;
	struct macsec_secy *secy;
	struct macsec_tx_sc *tx_sc;
	struct macsec_tx_sa *tx_sa;
	unsigned char assoc_num;
	struct nlattr *tb_sa[MACSEC_SA_ATTR_MAX + 1];
	int err;

	if (!attrs[MACSEC_ATTR_IFINDEX])
		return -EINVAL;

	if (parse_sa_config(attrs, tb_sa))
		return -EINVAL;

	if (!validate_add_txsa(tb_sa))
		return -EINVAL;

	rtnl_lock();
	dev = get_dev_from_nl(genl_info_net(info), attrs);
	if (IS_ERR(dev)) {
		rtnl_unlock();
		return PTR_ERR(dev);
	}

	secy = &macsec_priv(dev)->secy;
	tx_sc = &secy->tx_sc;

	assoc_num = nla_get_u8(tb_sa[MACSEC_SA_ATTR_AN]);

	if (nla_len(tb_sa[MACSEC_SA_ATTR_KEY]) != secy->key_len) {
		pr_notice("macsec: nl: add_txsa: bad key length: %d != %d\n",
			  nla_len(tb_sa[MACSEC_SA_ATTR_KEY]), secy->key_len);
		rtnl_unlock();
		return -EINVAL;
	}

	tx_sa = rtnl_dereference(tx_sc->sa[assoc_num]);
	if (tx_sa) {
		rtnl_unlock();
		return -EBUSY;
	}

	tx_sa = kmalloc(sizeof(*tx_sa), GFP_KERNEL);
	if (!tx_sa) {
		rtnl_unlock();
		return -ENOMEM;
	}

	err = init_tx_sa(tx_sa, nla_data(tb_sa[MACSEC_SA_ATTR_KEY]),
			 secy->key_len, secy->icv_len);
	if (err < 0) {
		kfree(tx_sa);
		rtnl_unlock();
		return err;
	}

	nla_memcpy(tx_sa->key.id, tb_sa[MACSEC_SA_ATTR_KEYID], MACSEC_KEYID_LEN);

	spin_lock_bh(&tx_sa->lock);
	tx_sa->next_pn = nla_get_u32(tb_sa[MACSEC_SA_ATTR_PN]);
	spin_unlock_bh(&tx_sa->lock);

	if (tb_sa[MACSEC_SA_ATTR_ACTIVE])
		tx_sa->active = !!nla_get_u8(tb_sa[MACSEC_SA_ATTR_ACTIVE]);

	if (assoc_num == tx_sc->encoding_sa && tx_sa->active)
		secy->operational = true;

	rcu_assign_pointer(tx_sc->sa[assoc_num], tx_sa);

	rtnl_unlock();

	return 0;
}