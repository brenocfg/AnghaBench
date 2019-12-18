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
struct nfsd_net {int /*<<< orphan*/  client_lock; int /*<<< orphan*/  close_lru; } ;
struct nfs4_openowner {int /*<<< orphan*/  oo_time; int /*<<< orphan*/  oo_close_lru; struct nfs4_ol_stateid* oo_last_closed_stid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sc_file; int /*<<< orphan*/  sc_count; TYPE_1__* sc_client; } ;
struct nfs4_ol_stateid {TYPE_2__ st_stid; int /*<<< orphan*/  st_stateowner; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_wq ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_openowner*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_stid (TYPE_2__*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 struct nfs4_openowner* openowner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_nfs4_file (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_all_access (struct nfs4_ol_stateid*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
move_to_close_lru(struct nfs4_ol_stateid *s, struct net *net)
{
	struct nfs4_ol_stateid *last;
	struct nfs4_openowner *oo = openowner(s->st_stateowner);
	struct nfsd_net *nn = net_generic(s->st_stid.sc_client->net,
						nfsd_net_id);

	dprintk("NFSD: move_to_close_lru nfs4_openowner %p\n", oo);

	/*
	 * We know that we hold one reference via nfsd4_close, and another
	 * "persistent" reference for the client. If the refcount is higher
	 * than 2, then there are still calls in progress that are using this
	 * stateid. We can't put the sc_file reference until they are finished.
	 * Wait for the refcount to drop to 2. Since it has been unhashed,
	 * there should be no danger of the refcount going back up again at
	 * this point.
	 */
	wait_event(close_wq, refcount_read(&s->st_stid.sc_count) == 2);

	release_all_access(s);
	if (s->st_stid.sc_file) {
		put_nfs4_file(s->st_stid.sc_file);
		s->st_stid.sc_file = NULL;
	}

	spin_lock(&nn->client_lock);
	last = oo->oo_last_closed_stid;
	oo->oo_last_closed_stid = s;
	list_move_tail(&oo->oo_close_lru, &nn->close_lru);
	oo->oo_time = get_seconds();
	spin_unlock(&nn->client_lock);
	if (last)
		nfs4_put_stid(&last->st_stid);
}