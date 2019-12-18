#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd_net {int /*<<< orphan*/  del_recall_lru; } ;
struct nfsd4_callback {int dummy; } ;
struct TYPE_6__ {TYPE_2__* sc_file; TYPE_1__* sc_client; } ;
struct nfs4_delegation {scalar_t__ dl_time; int /*<<< orphan*/  dl_recall_lru; TYPE_3__ dl_stid; } ;
struct TYPE_5__ {int /*<<< orphan*/  fi_fhandle; } ;
struct TYPE_4__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_delegations (int /*<<< orphan*/ *) ; 
 struct nfs4_delegation* cb_to_delegation (struct nfsd4_callback*) ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_lock ; 

__attribute__((used)) static void nfsd4_cb_recall_prepare(struct nfsd4_callback *cb)
{
	struct nfs4_delegation *dp = cb_to_delegation(cb);
	struct nfsd_net *nn = net_generic(dp->dl_stid.sc_client->net,
					  nfsd_net_id);

	block_delegations(&dp->dl_stid.sc_file->fi_fhandle);

	/*
	 * We can't do this in nfsd_break_deleg_cb because it is
	 * already holding inode->i_lock.
	 *
	 * If the dl_time != 0, then we know that it has already been
	 * queued for a lease break. Don't queue it again.
	 */
	spin_lock(&state_lock);
	if (dp->dl_time == 0) {
		dp->dl_time = get_seconds();
		list_add_tail(&dp->dl_recall_lru, &nn->del_recall_lru);
	}
	spin_unlock(&state_lock);
}