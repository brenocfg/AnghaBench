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
struct nfs4_client {int /*<<< orphan*/  cl_cb_null; int /*<<< orphan*/  cl_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD4_CLIENT_CB_KILL ; 
 int /*<<< orphan*/  callback_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_run_cb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nfsd4_shutdown_callback(struct nfs4_client *clp)
{
	set_bit(NFSD4_CLIENT_CB_KILL, &clp->cl_flags);
	/*
	 * Note this won't actually result in a null callback;
	 * instead, nfsd4_run_cb_null() will detect the killed
	 * client, destroy the rpc client, and stop:
	 */
	nfsd4_run_cb(&clp->cl_cb_null);
	flush_workqueue(callback_wq);
}