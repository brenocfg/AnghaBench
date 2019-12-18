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
typedef  scalar_t__ u32 ;
struct nfs_server {scalar_t__ dtsize; scalar_t__ rsize; scalar_t__ wsize; TYPE_2__* nfs_client; } ;
struct TYPE_3__ {scalar_t__ max_resp_sz; scalar_t__ max_rqst_sz; } ;
struct nfs4_session {TYPE_1__ fc_attrs; } ;
struct TYPE_4__ {struct nfs4_session* cl_session; } ;

/* Variables and functions */
 scalar_t__ nfs41_maxread_overhead ; 
 scalar_t__ nfs41_maxwrite_overhead ; 
 int /*<<< orphan*/  nfs4_has_session (TYPE_2__*) ; 

__attribute__((used)) static void nfs4_session_limit_rwsize(struct nfs_server *server)
{
#ifdef CONFIG_NFS_V4_1
	struct nfs4_session *sess;
	u32 server_resp_sz;
	u32 server_rqst_sz;

	if (!nfs4_has_session(server->nfs_client))
		return;
	sess = server->nfs_client->cl_session;
	server_resp_sz = sess->fc_attrs.max_resp_sz - nfs41_maxread_overhead;
	server_rqst_sz = sess->fc_attrs.max_rqst_sz - nfs41_maxwrite_overhead;

	if (server->dtsize > server_resp_sz)
		server->dtsize = server_resp_sz;
	if (server->rsize > server_resp_sz)
		server->rsize = server_resp_sz;
	if (server->wsize > server_rqst_sz)
		server->wsize = server_rqst_sz;
#endif /* CONFIG_NFS_V4_1 */
}