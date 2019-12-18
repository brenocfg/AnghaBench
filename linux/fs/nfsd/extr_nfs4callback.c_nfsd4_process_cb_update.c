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
struct nfsd4_session {int dummy; } ;
struct nfsd4_conn {struct nfsd4_session* cn_session; int /*<<< orphan*/  cn_xprt; } ;
struct nfsd4_callback {struct nfs4_client* cb_clp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cb_xprt; } ;
struct nfs4_client {int cl_flags; int /*<<< orphan*/  cl_lock; TYPE_1__ cl_cb_conn; int /*<<< orphan*/ * cl_cb_cred; int /*<<< orphan*/ * cl_cb_client; } ;
struct nfs4_cb_conn {int /*<<< orphan*/  cb_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NFSD4_CLIENT_CB_FLAG_MASK ; 
 int /*<<< orphan*/  NFSD4_CLIENT_CB_KILL ; 
 int /*<<< orphan*/  NFSD4_CLIENT_CB_UPDATE ; 
 struct nfsd4_conn* __nfsd4_find_backchannel (struct nfs4_client*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (struct nfs4_cb_conn*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  nfsd4_mark_cb_down (struct nfs4_client*,int) ; 
 int /*<<< orphan*/  put_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_shutdown_client (int /*<<< orphan*/ *) ; 
 int setup_callback_client (struct nfs4_client*,struct nfs4_cb_conn*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_xprt_put (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void nfsd4_process_cb_update(struct nfsd4_callback *cb)
{
	struct nfs4_cb_conn conn;
	struct nfs4_client *clp = cb->cb_clp;
	struct nfsd4_session *ses = NULL;
	struct nfsd4_conn *c;
	int err;

	/*
	 * This is either an update, or the client dying; in either case,
	 * kill the old client:
	 */
	if (clp->cl_cb_client) {
		rpc_shutdown_client(clp->cl_cb_client);
		clp->cl_cb_client = NULL;
		put_cred(clp->cl_cb_cred);
		clp->cl_cb_cred = NULL;
	}
	if (clp->cl_cb_conn.cb_xprt) {
		svc_xprt_put(clp->cl_cb_conn.cb_xprt);
		clp->cl_cb_conn.cb_xprt = NULL;
	}
	if (test_bit(NFSD4_CLIENT_CB_KILL, &clp->cl_flags))
		return;
	spin_lock(&clp->cl_lock);
	/*
	 * Only serialized callback code is allowed to clear these
	 * flags; main nfsd code can only set them:
	 */
	BUG_ON(!(clp->cl_flags & NFSD4_CLIENT_CB_FLAG_MASK));
	clear_bit(NFSD4_CLIENT_CB_UPDATE, &clp->cl_flags);
	memcpy(&conn, &cb->cb_clp->cl_cb_conn, sizeof(struct nfs4_cb_conn));
	c = __nfsd4_find_backchannel(clp);
	if (c) {
		svc_xprt_get(c->cn_xprt);
		conn.cb_xprt = c->cn_xprt;
		ses = c->cn_session;
	}
	spin_unlock(&clp->cl_lock);

	err = setup_callback_client(clp, &conn, ses);
	if (err) {
		nfsd4_mark_cb_down(clp, err);
		return;
	}
}