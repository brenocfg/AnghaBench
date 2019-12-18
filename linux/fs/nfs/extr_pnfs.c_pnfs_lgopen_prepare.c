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
struct nfs_server {TYPE_1__* pnfs_curr_ld; } ;
struct nfs_open_context {int dummy; } ;
struct nfs4_opendata {scalar_t__ state; TYPE_2__* dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CAP_LGOPEN ; 
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int PNFS_LAYOUTGET_ON_OPEN ; 
 int /*<<< orphan*/  _lgopen_prepare_attached (struct nfs4_opendata*,struct nfs_open_context*) ; 
 int /*<<< orphan*/  _lgopen_prepare_floating (struct nfs4_opendata*,struct nfs_open_context*) ; 
 int /*<<< orphan*/  nfs_server_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pnfs_enabled_sb (struct nfs_server*) ; 

void pnfs_lgopen_prepare(struct nfs4_opendata *data,
			 struct nfs_open_context *ctx)
{
	struct nfs_server *server = NFS_SERVER(data->dir->d_inode);

	if (!(pnfs_enabled_sb(server) &&
	      server->pnfs_curr_ld->flags & PNFS_LAYOUTGET_ON_OPEN))
		return;
	/* Could check on max_ops, but currently hardcoded high enough */
	if (!nfs_server_capable(data->dir->d_inode, NFS_CAP_LGOPEN))
		return;
	if (data->state)
		_lgopen_prepare_attached(data, ctx);
	else
		_lgopen_prepare_floating(data, ctx);
}