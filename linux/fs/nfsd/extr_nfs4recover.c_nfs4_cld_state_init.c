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
struct nfsd_net {int track_reclaim_completes; int /*<<< orphan*/  nr_reclaim_complete; scalar_t__ reclaim_str_hashtbl_size; int /*<<< orphan*/ * reclaim_str_hashtbl; } ;
struct net {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int CLIENT_HASH_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

__attribute__((used)) static int
nfs4_cld_state_init(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	int i;

	nn->reclaim_str_hashtbl = kmalloc_array(CLIENT_HASH_SIZE,
						sizeof(struct list_head),
						GFP_KERNEL);
	if (!nn->reclaim_str_hashtbl)
		return -ENOMEM;

	for (i = 0; i < CLIENT_HASH_SIZE; i++)
		INIT_LIST_HEAD(&nn->reclaim_str_hashtbl[i]);
	nn->reclaim_str_hashtbl_size = 0;
	nn->track_reclaim_completes = true;
	atomic_set(&nn->nr_reclaim_complete, 0);

	return 0;
}