#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct nfs_server {int flags; scalar_t__ rsize; scalar_t__ wsize; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; int options; scalar_t__ port; TYPE_6__* nfs_client; TYPE_4__* client; } ;
struct TYPE_11__ {scalar_t__ port; scalar_t__ addrlen; int /*<<< orphan*/  address; } ;
struct nfs_parsed_mount_data {int flags; scalar_t__ rsize; scalar_t__ wsize; scalar_t__ version; scalar_t__ minorversion; scalar_t__ retrans; unsigned int acregmin; unsigned int acregmax; unsigned int acdirmin; unsigned int acdirmax; unsigned int timeo; int options; TYPE_5__ nfs_server; int /*<<< orphan*/  auth_info; } ;
struct TYPE_12__ {scalar_t__ cl_minorversion; scalar_t__ cl_addrlen; int /*<<< orphan*/  cl_addr; TYPE_1__* rpc_ops; } ;
struct TYPE_10__ {TYPE_3__* cl_timeout; TYPE_2__* cl_auth; } ;
struct TYPE_9__ {scalar_t__ to_retries; unsigned int to_initval; } ;
struct TYPE_8__ {int /*<<< orphan*/  au_flavor; } ;
struct TYPE_7__ {scalar_t__ version; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int HZ ; 
 int NFS_OPTION_FSCACHE ; 
 int NFS_REMOUNT_CMP_FLAGMASK ; 
 int /*<<< orphan*/  nfs_auth_info_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_cmp_addr (struct sockaddr*,struct sockaddr*) ; 

__attribute__((used)) static int
nfs_compare_remount_data(struct nfs_server *nfss,
			 struct nfs_parsed_mount_data *data)
{
	if ((data->flags ^ nfss->flags) & NFS_REMOUNT_CMP_FLAGMASK ||
	    data->rsize != nfss->rsize ||
	    data->wsize != nfss->wsize ||
	    data->version != nfss->nfs_client->rpc_ops->version ||
	    data->minorversion != nfss->nfs_client->cl_minorversion ||
	    data->retrans != nfss->client->cl_timeout->to_retries ||
	    !nfs_auth_info_match(&data->auth_info, nfss->client->cl_auth->au_flavor) ||
	    data->acregmin != nfss->acregmin / HZ ||
	    data->acregmax != nfss->acregmax / HZ ||
	    data->acdirmin != nfss->acdirmin / HZ ||
	    data->acdirmax != nfss->acdirmax / HZ ||
	    data->timeo != (10U * nfss->client->cl_timeout->to_initval / HZ) ||
	    (data->options & NFS_OPTION_FSCACHE) != (nfss->options & NFS_OPTION_FSCACHE) ||
	    data->nfs_server.port != nfss->port ||
	    data->nfs_server.addrlen != nfss->nfs_client->cl_addrlen ||
	    !rpc_cmp_addr((struct sockaddr *)&data->nfs_server.address,
			  (struct sockaddr *)&nfss->nfs_client->cl_addr))
		return -EINVAL;

	return 0;
}