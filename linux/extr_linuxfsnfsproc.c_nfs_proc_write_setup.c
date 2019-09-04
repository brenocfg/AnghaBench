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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_clnt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stable; } ;
struct nfs_pgio_header {TYPE_1__ args; } ;

/* Variables and functions */
 size_t NFSPROC_WRITE ; 
 int /*<<< orphan*/  NFS_FILE_SYNC ; 
 int /*<<< orphan*/ * nfs_procedures ; 

__attribute__((used)) static void nfs_proc_write_setup(struct nfs_pgio_header *hdr,
				 struct rpc_message *msg,
				 struct rpc_clnt **clnt)
{
	/* Note: NFSv2 ignores @stable and always uses NFS_FILE_SYNC */
	hdr->args.stable = NFS_FILE_SYNC;
	msg->rpc_proc = &nfs_procedures[NFSPROC_WRITE];
}