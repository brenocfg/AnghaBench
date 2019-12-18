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
typedef  int u32 ;
struct net {int dummy; } ;
struct l2tp_tunnel_cfg {int encap; int /*<<< orphan*/  debug; } ;
struct l2tp_tunnel {int version; int tunnel_id; int peer_tunnel_id; int acpt_newsess; int encap; int fd; int /*<<< orphan*/  list; int /*<<< orphan*/  del_work; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  debug; int /*<<< orphan*/  hlist_lock; int /*<<< orphan*/ * name; int /*<<< orphan*/  magic; } ;
typedef  enum l2tp_encap_type { ____Placeholder_l2tp_encap_type } l2tp_encap_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2TP_DEFAULT_DEBUG_FLAGS ; 
 int L2TP_ENCAPTYPE_UDP ; 
 int /*<<< orphan*/  L2TP_TUNNEL_MAGIC ; 
 struct l2tp_tunnel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2tp_tunnel_del_work ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int) ; 

int l2tp_tunnel_create(struct net *net, int fd, int version, u32 tunnel_id, u32 peer_tunnel_id, struct l2tp_tunnel_cfg *cfg, struct l2tp_tunnel **tunnelp)
{
	struct l2tp_tunnel *tunnel = NULL;
	int err;
	enum l2tp_encap_type encap = L2TP_ENCAPTYPE_UDP;

	if (cfg != NULL)
		encap = cfg->encap;

	tunnel = kzalloc(sizeof(struct l2tp_tunnel), GFP_KERNEL);
	if (tunnel == NULL) {
		err = -ENOMEM;
		goto err;
	}

	tunnel->version = version;
	tunnel->tunnel_id = tunnel_id;
	tunnel->peer_tunnel_id = peer_tunnel_id;
	tunnel->debug = L2TP_DEFAULT_DEBUG_FLAGS;

	tunnel->magic = L2TP_TUNNEL_MAGIC;
	sprintf(&tunnel->name[0], "tunl %u", tunnel_id);
	rwlock_init(&tunnel->hlist_lock);
	tunnel->acpt_newsess = true;

	if (cfg != NULL)
		tunnel->debug = cfg->debug;

	tunnel->encap = encap;

	refcount_set(&tunnel->ref_count, 1);
	tunnel->fd = fd;

	/* Init delete workqueue struct */
	INIT_WORK(&tunnel->del_work, l2tp_tunnel_del_work);

	INIT_LIST_HEAD(&tunnel->list);

	err = 0;
err:
	if (tunnelp)
		*tunnelp = tunnel;

	return err;
}