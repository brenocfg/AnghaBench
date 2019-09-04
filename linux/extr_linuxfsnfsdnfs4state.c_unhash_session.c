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
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_session {struct nfs4_client* se_client; int /*<<< orphan*/  se_perclnt; int /*<<< orphan*/  se_hash; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unhash_session(struct nfsd4_session *ses)
{
	struct nfs4_client *clp = ses->se_client;
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_assert_held(&nn->client_lock);

	list_del(&ses->se_hash);
	spin_lock(&ses->se_client->cl_lock);
	list_del(&ses->se_perclnt);
	spin_unlock(&ses->se_client->cl_lock);
}