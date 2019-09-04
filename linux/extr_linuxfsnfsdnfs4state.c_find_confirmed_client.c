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
struct nfsd_net {int /*<<< orphan*/  client_lock; struct list_head* conf_id_hashtbl; } ;
struct nfs4_client {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  clientid_t ;

/* Variables and functions */
 struct nfs4_client* find_client_in_id_table (struct list_head*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_client *
find_confirmed_client(clientid_t *clid, bool sessions, struct nfsd_net *nn)
{
	struct list_head *tbl = nn->conf_id_hashtbl;

	lockdep_assert_held(&nn->client_lock);
	return find_client_in_id_table(tbl, clid, sessions);
}