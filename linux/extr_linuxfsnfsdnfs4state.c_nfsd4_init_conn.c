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
struct svc_rqst {int dummy; } ;
struct nfsd4_session {int /*<<< orphan*/  se_client; } ;
struct nfsd4_conn {int /*<<< orphan*/  cn_xpt_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd4_conn_lost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_hash_conn (struct nfsd4_conn*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_probe_callback_sync (int /*<<< orphan*/ ) ; 
 int nfsd4_register_conn (struct nfsd4_conn*) ; 

__attribute__((used)) static void nfsd4_init_conn(struct svc_rqst *rqstp, struct nfsd4_conn *conn, struct nfsd4_session *ses)
{
	int ret;

	nfsd4_hash_conn(conn, ses);
	ret = nfsd4_register_conn(conn);
	if (ret)
		/* oops; xprt is already down: */
		nfsd4_conn_lost(&conn->cn_xpt_user);
	/* We may have gained or lost a callback channel: */
	nfsd4_probe_callback_sync(ses->se_client);
}