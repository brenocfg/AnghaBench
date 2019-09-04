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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; } ;
struct net {int dummy; } ;
struct l2tp_tunnel {int dummy; } ;
struct l2tp_session_cfg {int /*<<< orphan*/  ifname; } ;
struct l2tp_session {char* ifname; int /*<<< orphan*/  show; int /*<<< orphan*/  session_close; int /*<<< orphan*/  recv_skb; } ;
struct l2tp_eth_sess {int /*<<< orphan*/  dev; } ;
struct l2tp_eth {struct l2tp_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_L2TP_DEBUGFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int IFNAMSIZ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct l2tp_session*) ; 
 int /*<<< orphan*/  L2TP_ETH_DEV_NAME ; 
 unsigned char NET_NAME_ENUM ; 
 unsigned char NET_NAME_USER ; 
 int PTR_ERR (struct l2tp_session*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int,char*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_eth_adjust_mtu (struct l2tp_tunnel*,struct l2tp_session*,struct net_device*) ; 
 int /*<<< orphan*/  l2tp_eth_delete ; 
 int /*<<< orphan*/  l2tp_eth_dev_recv ; 
 int /*<<< orphan*/  l2tp_eth_dev_setup ; 
 int /*<<< orphan*/  l2tp_eth_show ; 
 struct l2tp_session* l2tp_session_create (int,struct l2tp_tunnel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct l2tp_session_cfg*) ; 
 int /*<<< orphan*/  l2tp_session_dec_refcount (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_session_delete (struct l2tp_session*) ; 
 int /*<<< orphan*/  l2tp_session_inc_refcount (struct l2tp_session*) ; 
 struct l2tp_eth_sess* l2tp_session_priv (struct l2tp_session*) ; 
 int l2tp_session_register (struct l2tp_session*,struct l2tp_tunnel*) ; 
 struct l2tp_eth* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int l2tp_eth_create(struct net *net, struct l2tp_tunnel *tunnel,
			   u32 session_id, u32 peer_session_id,
			   struct l2tp_session_cfg *cfg)
{
	unsigned char name_assign_type;
	struct net_device *dev;
	char name[IFNAMSIZ];
	struct l2tp_session *session;
	struct l2tp_eth *priv;
	struct l2tp_eth_sess *spriv;
	int rc;

	if (cfg->ifname) {
		strlcpy(name, cfg->ifname, IFNAMSIZ);
		name_assign_type = NET_NAME_USER;
	} else {
		strcpy(name, L2TP_ETH_DEV_NAME);
		name_assign_type = NET_NAME_ENUM;
	}

	session = l2tp_session_create(sizeof(*spriv), tunnel, session_id,
				      peer_session_id, cfg);
	if (IS_ERR(session)) {
		rc = PTR_ERR(session);
		goto err;
	}

	dev = alloc_netdev(sizeof(*priv), name, name_assign_type,
			   l2tp_eth_dev_setup);
	if (!dev) {
		rc = -ENOMEM;
		goto err_sess;
	}

	dev_net_set(dev, net);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	l2tp_eth_adjust_mtu(tunnel, session, dev);

	priv = netdev_priv(dev);
	priv->session = session;

	session->recv_skb = l2tp_eth_dev_recv;
	session->session_close = l2tp_eth_delete;
	if (IS_ENABLED(CONFIG_L2TP_DEBUGFS))
		session->show = l2tp_eth_show;

	spriv = l2tp_session_priv(session);

	l2tp_session_inc_refcount(session);

	rtnl_lock();

	/* Register both device and session while holding the rtnl lock. This
	 * ensures that l2tp_eth_delete() will see that there's a device to
	 * unregister, even if it happened to run before we assign spriv->dev.
	 */
	rc = l2tp_session_register(session, tunnel);
	if (rc < 0) {
		rtnl_unlock();
		goto err_sess_dev;
	}

	rc = register_netdevice(dev);
	if (rc < 0) {
		rtnl_unlock();
		l2tp_session_delete(session);
		l2tp_session_dec_refcount(session);
		free_netdev(dev);

		return rc;
	}

	strlcpy(session->ifname, dev->name, IFNAMSIZ);
	rcu_assign_pointer(spriv->dev, dev);

	rtnl_unlock();

	l2tp_session_dec_refcount(session);

	__module_get(THIS_MODULE);

	return 0;

err_sess_dev:
	l2tp_session_dec_refcount(session);
	free_netdev(dev);
err_sess:
	kfree(session);
err:
	return rc;
}