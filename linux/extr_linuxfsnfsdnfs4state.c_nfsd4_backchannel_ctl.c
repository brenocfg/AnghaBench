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
struct nfsd4_backchannel_ctl {int /*<<< orphan*/  bc_cb_sec; int /*<<< orphan*/  bc_cb_program; } ;
union nfsd4_op_u {struct nfsd4_backchannel_ctl backchannel_ctl; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct nfsd4_session {int /*<<< orphan*/  se_client; int /*<<< orphan*/  se_cb_sec; int /*<<< orphan*/  se_cb_prog; } ;
struct nfsd4_compound_state {struct nfsd4_session* session; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_check_cb_sec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_probe_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__be32 nfsd4_backchannel_ctl(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_backchannel_ctl *bc = &u->backchannel_ctl;
	struct nfsd4_session *session = cstate->session;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	__be32 status;

	status = nfsd4_check_cb_sec(&bc->bc_cb_sec);
	if (status)
		return status;
	spin_lock(&nn->client_lock);
	session->se_cb_prog = bc->bc_cb_program;
	session->se_cb_sec = bc->bc_cb_sec;
	spin_unlock(&nn->client_lock);

	nfsd4_probe_callback(session->se_client);

	return nfs_ok;
}