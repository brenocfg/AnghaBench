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
struct TYPE_2__ {int block_opens; int /*<<< orphan*/  list; } ;
struct nfsd_net {int grace_ended; int /*<<< orphan*/ * conf_id_hashtbl; int /*<<< orphan*/ * unconf_id_hashtbl; int /*<<< orphan*/  laundromat_work; int /*<<< orphan*/  blocked_locks_lru; int /*<<< orphan*/  blocked_locks_lock; int /*<<< orphan*/  s2s_cp_stateids; int /*<<< orphan*/  s2s_cp_lock; int /*<<< orphan*/  client_lock; int /*<<< orphan*/  del_recall_lru; int /*<<< orphan*/  close_lru; int /*<<< orphan*/  client_lru; TYPE_1__ nfsd4_manager; int /*<<< orphan*/  boot_time; void* unconf_name_tree; void* conf_name_tree; int /*<<< orphan*/ * sessionid_hashtbl; } ;
struct net {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int CLIENT_HASH_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 int SESSION_HASH_SIZE ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  laundromat_main ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_state_create_net(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	int i;

	nn->conf_id_hashtbl = kmalloc_array(CLIENT_HASH_SIZE,
					    sizeof(struct list_head),
					    GFP_KERNEL);
	if (!nn->conf_id_hashtbl)
		goto err;
	nn->unconf_id_hashtbl = kmalloc_array(CLIENT_HASH_SIZE,
					      sizeof(struct list_head),
					      GFP_KERNEL);
	if (!nn->unconf_id_hashtbl)
		goto err_unconf_id;
	nn->sessionid_hashtbl = kmalloc_array(SESSION_HASH_SIZE,
					      sizeof(struct list_head),
					      GFP_KERNEL);
	if (!nn->sessionid_hashtbl)
		goto err_sessionid;

	for (i = 0; i < CLIENT_HASH_SIZE; i++) {
		INIT_LIST_HEAD(&nn->conf_id_hashtbl[i]);
		INIT_LIST_HEAD(&nn->unconf_id_hashtbl[i]);
	}
	for (i = 0; i < SESSION_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nn->sessionid_hashtbl[i]);
	nn->conf_name_tree = RB_ROOT;
	nn->unconf_name_tree = RB_ROOT;
	nn->boot_time = get_seconds();
	nn->grace_ended = false;
	nn->nfsd4_manager.block_opens = true;
	INIT_LIST_HEAD(&nn->nfsd4_manager.list);
	INIT_LIST_HEAD(&nn->client_lru);
	INIT_LIST_HEAD(&nn->close_lru);
	INIT_LIST_HEAD(&nn->del_recall_lru);
	spin_lock_init(&nn->client_lock);
	spin_lock_init(&nn->s2s_cp_lock);
	idr_init(&nn->s2s_cp_stateids);

	spin_lock_init(&nn->blocked_locks_lock);
	INIT_LIST_HEAD(&nn->blocked_locks_lru);

	INIT_DELAYED_WORK(&nn->laundromat_work, laundromat_main);
	get_net(net);

	return 0;

err_sessionid:
	kfree(nn->unconf_id_hashtbl);
err_unconf_id:
	kfree(nn->conf_id_hashtbl);
err:
	return -ENOMEM;
}