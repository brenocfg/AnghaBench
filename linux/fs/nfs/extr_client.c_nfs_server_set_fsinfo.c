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
struct nfs_server {int rsize; int wsize; int rpages; int wpages; int dtsize; int flags; int /*<<< orphan*/  client; int /*<<< orphan*/  clone_blksize; int /*<<< orphan*/  time_delta; int /*<<< orphan*/  maxfilesize; scalar_t__ acdirmax; scalar_t__ acdirmin; scalar_t__ acregmax; scalar_t__ acregmin; int /*<<< orphan*/  wtmult; } ;
struct nfs_fsinfo {int rtpref; int wtpref; int rtmax; int wtmax; int dtpref; int /*<<< orphan*/  clone_blksize; int /*<<< orphan*/  time_delta; int /*<<< orphan*/  maxfilesize; int /*<<< orphan*/  wtmult; } ;

/* Variables and functions */
 void* NFS_MAX_FILE_IO_SIZE ; 
 int NFS_MAX_READDIR_PAGES ; 
 int NFS_MOUNT_NOAC ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  nfs_block_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* nfs_block_size (int,int /*<<< orphan*/ *) ; 
 int rpc_max_payload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_setbufsize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void nfs_server_set_fsinfo(struct nfs_server *server,
				  struct nfs_fsinfo *fsinfo)
{
	unsigned long max_rpc_payload;

	/* Work out a lot of parameters */
	if (server->rsize == 0)
		server->rsize = nfs_block_size(fsinfo->rtpref, NULL);
	if (server->wsize == 0)
		server->wsize = nfs_block_size(fsinfo->wtpref, NULL);

	if (fsinfo->rtmax >= 512 && server->rsize > fsinfo->rtmax)
		server->rsize = nfs_block_size(fsinfo->rtmax, NULL);
	if (fsinfo->wtmax >= 512 && server->wsize > fsinfo->wtmax)
		server->wsize = nfs_block_size(fsinfo->wtmax, NULL);

	max_rpc_payload = nfs_block_size(rpc_max_payload(server->client), NULL);
	if (server->rsize > max_rpc_payload)
		server->rsize = max_rpc_payload;
	if (server->rsize > NFS_MAX_FILE_IO_SIZE)
		server->rsize = NFS_MAX_FILE_IO_SIZE;
	server->rpages = (server->rsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	if (server->wsize > max_rpc_payload)
		server->wsize = max_rpc_payload;
	if (server->wsize > NFS_MAX_FILE_IO_SIZE)
		server->wsize = NFS_MAX_FILE_IO_SIZE;
	server->wpages = (server->wsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	server->wtmult = nfs_block_bits(fsinfo->wtmult, NULL);

	server->dtsize = nfs_block_size(fsinfo->dtpref, NULL);
	if (server->dtsize > PAGE_SIZE * NFS_MAX_READDIR_PAGES)
		server->dtsize = PAGE_SIZE * NFS_MAX_READDIR_PAGES;
	if (server->dtsize > server->rsize)
		server->dtsize = server->rsize;

	if (server->flags & NFS_MOUNT_NOAC) {
		server->acregmin = server->acregmax = 0;
		server->acdirmin = server->acdirmax = 0;
	}

	server->maxfilesize = fsinfo->maxfilesize;

	server->time_delta = fsinfo->time_delta;

	server->clone_blksize = fsinfo->clone_blksize;
	/* We're airborne Set socket buffersize */
	rpc_setbufsize(server->client, server->wsize + 100, server->rsize + 100);
}