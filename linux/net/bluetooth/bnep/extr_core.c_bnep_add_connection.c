#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct socket {int /*<<< orphan*/  sk; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/ ** dev_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  msg_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** h_dest; int /*<<< orphan*/ ** h_source; } ;
struct bnep_session {scalar_t__ state; int flags; long long mc_filter; int /*<<< orphan*/  task; TYPE_3__ msg; int /*<<< orphan*/  role; struct socket* sock; struct net_device* dev; TYPE_2__ eh; } ;
struct bnep_connadd_req {int flags; char* device; int /*<<< orphan*/  role; } ;
struct TYPE_8__ {TYPE_1__* chan; } ;
struct TYPE_5__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNEP_SETUP_RESPONSE ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int EBADFD ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct bnep_session* __bnep_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __bnep_link_session (struct bnep_session*) ; 
 int /*<<< orphan*/  __bnep_unlink_session (struct bnep_session*) ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  baswap (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_get_device (struct bnep_session*) ; 
 int /*<<< orphan*/  bnep_net_setup ; 
 int /*<<< orphan*/  bnep_session ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 int /*<<< orphan*/  bnep_set_default_proto_filter (struct bnep_session*) ; 
 int /*<<< orphan*/  bnep_type ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct bnep_session*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_is_socket (struct socket*) ; 
 TYPE_4__* l2cap_pi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct bnep_session* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int bnep_add_connection(struct bnep_connadd_req *req, struct socket *sock)
{
	u32 valid_flags = BIT(BNEP_SETUP_RESPONSE);
	struct net_device *dev;
	struct bnep_session *s, *ss;
	u8 dst[ETH_ALEN], src[ETH_ALEN];
	int err;

	BT_DBG("");

	if (!l2cap_is_socket(sock))
		return -EBADFD;

	if (req->flags & ~valid_flags)
		return -EINVAL;

	baswap((void *) dst, &l2cap_pi(sock->sk)->chan->dst);
	baswap((void *) src, &l2cap_pi(sock->sk)->chan->src);

	/* session struct allocated as private part of net_device */
	dev = alloc_netdev(sizeof(struct bnep_session),
			   (*req->device) ? req->device : "bnep%d",
			   NET_NAME_UNKNOWN,
			   bnep_net_setup);
	if (!dev)
		return -ENOMEM;

	down_write(&bnep_session_sem);

	ss = __bnep_get_session(dst);
	if (ss && ss->state == BT_CONNECTED) {
		err = -EEXIST;
		goto failed;
	}

	s = netdev_priv(dev);

	/* This is rx header therefore addresses are swapped.
	 * ie. eh.h_dest is our local address. */
	memcpy(s->eh.h_dest,   &src, ETH_ALEN);
	memcpy(s->eh.h_source, &dst, ETH_ALEN);
	memcpy(dev->dev_addr, s->eh.h_dest, ETH_ALEN);

	s->dev   = dev;
	s->sock  = sock;
	s->role  = req->role;
	s->state = BT_CONNECTED;
	s->flags = req->flags;

	s->msg.msg_flags = MSG_NOSIGNAL;

#ifdef CONFIG_BT_BNEP_MC_FILTER
	/* Set default mc filter to not filter out any mc addresses
	 * as defined in the BNEP specification (revision 0.95a)
	 * http://grouper.ieee.org/groups/802/15/Bluetooth/BNEP.pdf
	 */
	s->mc_filter = ~0LL;
#endif

#ifdef CONFIG_BT_BNEP_PROTO_FILTER
	/* Set default protocol filter */
	bnep_set_default_proto_filter(s);
#endif

	SET_NETDEV_DEV(dev, bnep_get_device(s));
	SET_NETDEV_DEVTYPE(dev, &bnep_type);

	err = register_netdev(dev);
	if (err)
		goto failed;

	__bnep_link_session(s);

	__module_get(THIS_MODULE);
	s->task = kthread_run(bnep_session, s, "kbnepd %s", dev->name);
	if (IS_ERR(s->task)) {
		/* Session thread start failed, gotta cleanup. */
		module_put(THIS_MODULE);
		unregister_netdev(dev);
		__bnep_unlink_session(s);
		err = PTR_ERR(s->task);
		goto failed;
	}

	up_write(&bnep_session_sem);
	strcpy(req->device, dev->name);
	return 0;

failed:
	up_write(&bnep_session_sem);
	free_netdev(dev);
	return err;
}