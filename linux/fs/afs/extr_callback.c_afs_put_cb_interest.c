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
struct afs_vol_interest {scalar_t__ usage; TYPE_1__* server; int /*<<< orphan*/  srv_link; struct afs_vol_interest* vol_interest; int /*<<< orphan*/  cb_vlink; } ;
struct afs_net {int dummy; } ;
struct afs_cb_interest {scalar_t__ usage; TYPE_1__* server; int /*<<< orphan*/  srv_link; struct afs_cb_interest* vol_interest; int /*<<< orphan*/  cb_vlink; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_break_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  afs_put_server (struct afs_net*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_server_trace_put_cbi ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct afs_vol_interest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 scalar_t__ refcount_dec_and_test (scalar_t__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void afs_put_cb_interest(struct afs_net *net, struct afs_cb_interest *cbi)
{
	struct afs_vol_interest *vi;

	if (cbi && refcount_dec_and_test(&cbi->usage)) {
		if (!hlist_unhashed(&cbi->cb_vlink)) {
			write_lock(&cbi->server->cb_break_lock);

			hlist_del_init(&cbi->cb_vlink);
			vi = cbi->vol_interest;
			cbi->vol_interest = NULL;
			if (--vi->usage == 0)
				hlist_del(&vi->srv_link);
			else
				vi = NULL;

			write_unlock(&cbi->server->cb_break_lock);
			if (vi)
				kfree_rcu(vi, rcu);
			afs_put_server(net, cbi->server, afs_server_trace_put_cbi);
		}
		kfree_rcu(cbi, rcu);
	}
}