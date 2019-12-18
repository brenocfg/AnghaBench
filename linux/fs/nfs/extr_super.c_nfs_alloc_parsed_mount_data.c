#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  protocol; void* port; } ;
struct TYPE_5__ {void* port; } ;
struct nfs_parsed_mount_data {int need_mount; int /*<<< orphan*/ * lsm_opts; int /*<<< orphan*/  net; scalar_t__ minorversion; int /*<<< orphan*/  selected_flavor; TYPE_2__ nfs_server; TYPE_1__ mount_server; int /*<<< orphan*/  acdirmax; int /*<<< orphan*/  acdirmin; int /*<<< orphan*/  acregmax; int /*<<< orphan*/  acregmin; int /*<<< orphan*/  retrans; int /*<<< orphan*/  timeo; } ;
struct TYPE_8__ {TYPE_3__* nsproxy; } ;
struct TYPE_7__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFS_DEF_ACDIRMAX ; 
 int /*<<< orphan*/  NFS_DEF_ACDIRMIN ; 
 int /*<<< orphan*/  NFS_DEF_ACREGMAX ; 
 int /*<<< orphan*/  NFS_DEF_ACREGMIN ; 
 void* NFS_UNSPEC_PORT ; 
 int /*<<< orphan*/  NFS_UNSPEC_RETRANS ; 
 int /*<<< orphan*/  NFS_UNSPEC_TIMEO ; 
 int /*<<< orphan*/  RPC_AUTH_MAXFLAVOR ; 
 int /*<<< orphan*/  XPRT_TRANSPORT_TCP ; 
 TYPE_4__* current ; 
 struct nfs_parsed_mount_data* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs_parsed_mount_data *nfs_alloc_parsed_mount_data(void)
{
	struct nfs_parsed_mount_data *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data) {
		data->timeo		= NFS_UNSPEC_TIMEO;
		data->retrans		= NFS_UNSPEC_RETRANS;
		data->acregmin		= NFS_DEF_ACREGMIN;
		data->acregmax		= NFS_DEF_ACREGMAX;
		data->acdirmin		= NFS_DEF_ACDIRMIN;
		data->acdirmax		= NFS_DEF_ACDIRMAX;
		data->mount_server.port	= NFS_UNSPEC_PORT;
		data->nfs_server.port	= NFS_UNSPEC_PORT;
		data->nfs_server.protocol = XPRT_TRANSPORT_TCP;
		data->selected_flavor	= RPC_AUTH_MAXFLAVOR;
		data->minorversion	= 0;
		data->need_mount	= true;
		data->net		= current->nsproxy->net_ns;
		data->lsm_opts		= NULL;
	}
	return data;
}