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
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct nfsd4_create_session {int flags; int /*<<< orphan*/  fore_channel; scalar_t__ seqid; TYPE_1__ sessionid; int /*<<< orphan*/  clientid; int /*<<< orphan*/  back_channel; int /*<<< orphan*/  cb_sec; } ;
union nfsd4_op_u {struct nfsd4_create_session create_session; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct sockaddr {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct nfsd4_session {TYPE_2__ se_sessionid; } ;
struct nfsd4_conn {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfsd4_clid_slot {scalar_t__ sl_seqid; } ;
struct nfs4_client {int /*<<< orphan*/  cl_name; struct nfsd4_clid_slot cl_cs_slot; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cred; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_MAX_SESSIONID_LEN ; 
 int SESSION4_FLAG_MASK_A ; 
 int SESSION4_PERSIST ; 
 int SESSION4_RDMA ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __free_session (struct nfsd4_session*) ; 
 struct nfsd4_conn* alloc_conn_from_crses (struct svc_rqst*,struct nfsd4_create_session*) ; 
 struct nfsd4_session* alloc_session (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ check_backchannel_attrs (int /*<<< orphan*/ *) ; 
 scalar_t__ check_forechannel_attrs (int /*<<< orphan*/ *,struct nfsd_net*) ; 
 scalar_t__ check_slot_seqid (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 struct nfs4_client* find_confirmed_client_by_name (int /*<<< orphan*/ *,struct nfsd_net*) ; 
 struct nfs4_client* find_unconfirmed_client (int /*<<< orphan*/ *,int,struct nfsd_net*) ; 
 int /*<<< orphan*/  free_conn (struct nfsd4_conn*) ; 
 int /*<<< orphan*/  init_session (struct svc_rqst*,struct nfsd4_session*,struct nfs4_client*,struct nfsd4_create_session*) ; 
 scalar_t__ mark_client_expired_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_to_confirmed (struct nfs4_client*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_cache_create_session (struct nfsd4_create_session*,struct nfsd4_clid_slot*,scalar_t__) ; 
 scalar_t__ nfsd4_check_cb_sec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_get_session_locked (struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_init_conn (struct svc_rqst*,struct nfsd4_conn*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_mach_creds_match (struct nfs4_client*,struct svc_rqst*) ; 
 int /*<<< orphan*/  nfsd4_put_drc_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_put_session (struct nfsd4_session*) ; 
 scalar_t__ nfsd4_replay_create_session (struct nfsd4_create_session*,struct nfsd4_clid_slot*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 scalar_t__ nfserr_clid_inuse ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_jukebox ; 
 scalar_t__ nfserr_replay_cache ; 
 scalar_t__ nfserr_seq_misordered ; 
 scalar_t__ nfserr_stale_clientid ; 
 scalar_t__ nfserr_wrong_cred ; 
 int /*<<< orphan*/  rpc_cmp_addr (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  same_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 

__be32
nfsd4_create_session(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate, union nfsd4_op_u *u)
{
	struct nfsd4_create_session *cr_ses = &u->create_session;
	struct sockaddr *sa = svc_addr(rqstp);
	struct nfs4_client *conf, *unconf;
	struct nfs4_client *old = NULL;
	struct nfsd4_session *new;
	struct nfsd4_conn *conn;
	struct nfsd4_clid_slot *cs_slot = NULL;
	__be32 status = 0;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	if (cr_ses->flags & ~SESSION4_FLAG_MASK_A)
		return nfserr_inval;
	status = nfsd4_check_cb_sec(&cr_ses->cb_sec);
	if (status)
		return status;
	status = check_forechannel_attrs(&cr_ses->fore_channel, nn);
	if (status)
		return status;
	status = check_backchannel_attrs(&cr_ses->back_channel);
	if (status)
		goto out_release_drc_mem;
	status = nfserr_jukebox;
	new = alloc_session(&cr_ses->fore_channel, &cr_ses->back_channel);
	if (!new)
		goto out_release_drc_mem;
	conn = alloc_conn_from_crses(rqstp, cr_ses);
	if (!conn)
		goto out_free_session;

	spin_lock(&nn->client_lock);
	unconf = find_unconfirmed_client(&cr_ses->clientid, true, nn);
	conf = find_confirmed_client(&cr_ses->clientid, true, nn);
	WARN_ON_ONCE(conf && unconf);

	if (conf) {
		status = nfserr_wrong_cred;
		if (!nfsd4_mach_creds_match(conf, rqstp))
			goto out_free_conn;
		cs_slot = &conf->cl_cs_slot;
		status = check_slot_seqid(cr_ses->seqid, cs_slot->sl_seqid, 0);
		if (status) {
			if (status == nfserr_replay_cache)
				status = nfsd4_replay_create_session(cr_ses, cs_slot);
			goto out_free_conn;
		}
	} else if (unconf) {
		if (!same_creds(&unconf->cl_cred, &rqstp->rq_cred) ||
		    !rpc_cmp_addr(sa, (struct sockaddr *) &unconf->cl_addr)) {
			status = nfserr_clid_inuse;
			goto out_free_conn;
		}
		status = nfserr_wrong_cred;
		if (!nfsd4_mach_creds_match(unconf, rqstp))
			goto out_free_conn;
		cs_slot = &unconf->cl_cs_slot;
		status = check_slot_seqid(cr_ses->seqid, cs_slot->sl_seqid, 0);
		if (status) {
			/* an unconfirmed replay returns misordered */
			status = nfserr_seq_misordered;
			goto out_free_conn;
		}
		old = find_confirmed_client_by_name(&unconf->cl_name, nn);
		if (old) {
			status = mark_client_expired_locked(old);
			if (status) {
				old = NULL;
				goto out_free_conn;
			}
		}
		move_to_confirmed(unconf);
		conf = unconf;
	} else {
		status = nfserr_stale_clientid;
		goto out_free_conn;
	}
	status = nfs_ok;
	/* Persistent sessions are not supported */
	cr_ses->flags &= ~SESSION4_PERSIST;
	/* Upshifting from TCP to RDMA is not supported */
	cr_ses->flags &= ~SESSION4_RDMA;

	init_session(rqstp, new, conf, cr_ses);
	nfsd4_get_session_locked(new);

	memcpy(cr_ses->sessionid.data, new->se_sessionid.data,
	       NFS4_MAX_SESSIONID_LEN);
	cs_slot->sl_seqid++;
	cr_ses->seqid = cs_slot->sl_seqid;

	/* cache solo and embedded create sessions under the client_lock */
	nfsd4_cache_create_session(cr_ses, cs_slot, status);
	spin_unlock(&nn->client_lock);
	/* init connection and backchannel */
	nfsd4_init_conn(rqstp, conn, new);
	nfsd4_put_session(new);
	if (old)
		expire_client(old);
	return status;
out_free_conn:
	spin_unlock(&nn->client_lock);
	free_conn(conn);
	if (old)
		expire_client(old);
out_free_session:
	__free_session(new);
out_release_drc_mem:
	nfsd4_put_drc_mem(&cr_ses->fore_channel);
	return status;
}