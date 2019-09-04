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
struct nfsd4_bind_conn_to_session {int /*<<< orphan*/  dir; int /*<<< orphan*/  sessionid; } ;
union nfsd4_op_u {struct nfsd4_bind_conn_to_session bind_conn_to_session; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_session {int /*<<< orphan*/  se_client; } ;
struct nfsd4_conn {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 struct net* SVC_NET (struct svc_rqst*) ; 
 struct nfsd4_conn* alloc_conn (struct svc_rqst*,int /*<<< orphan*/ ) ; 
 struct nfsd4_session* find_in_sessionid_hashtbl (int /*<<< orphan*/ *,struct net*,scalar_t__*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_init_conn (struct svc_rqst*,struct nfsd4_conn*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_last_compound_op (struct svc_rqst*) ; 
 int /*<<< orphan*/  nfsd4_mach_creds_match (int /*<<< orphan*/ ,struct svc_rqst*) ; 
 scalar_t__ nfsd4_map_bcts_dir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_put_session (struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_jukebox ; 
 scalar_t__ nfserr_not_only_op ; 
 scalar_t__ nfserr_wrong_cred ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__be32 nfsd4_bind_conn_to_session(struct svc_rqst *rqstp,
		     struct nfsd4_compound_state *cstate,
		     union nfsd4_op_u *u)
{
	struct nfsd4_bind_conn_to_session *bcts = &u->bind_conn_to_session;
	__be32 status;
	struct nfsd4_conn *conn;
	struct nfsd4_session *session;
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	if (!nfsd4_last_compound_op(rqstp))
		return nfserr_not_only_op;
	spin_lock(&nn->client_lock);
	session = find_in_sessionid_hashtbl(&bcts->sessionid, net, &status);
	spin_unlock(&nn->client_lock);
	if (!session)
		goto out_no_session;
	status = nfserr_wrong_cred;
	if (!nfsd4_mach_creds_match(session->se_client, rqstp))
		goto out;
	status = nfsd4_map_bcts_dir(&bcts->dir);
	if (status)
		goto out;
	conn = alloc_conn(rqstp, bcts->dir);
	status = nfserr_jukebox;
	if (!conn)
		goto out;
	nfsd4_init_conn(rqstp, conn, session);
	status = nfs_ok;
out:
	nfsd4_put_session(session);
out_no_session:
	return status;
}