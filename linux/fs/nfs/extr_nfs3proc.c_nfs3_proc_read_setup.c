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
struct rpc_message {int /*<<< orphan*/ * rpc_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/  replen; } ;
struct nfs_pgio_header {int /*<<< orphan*/  inode; TYPE_1__ args; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_hdrsize; } ;

/* Variables and functions */
 size_t NFS3PROC_READ ; 
 TYPE_2__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 

__attribute__((used)) static void nfs3_proc_read_setup(struct nfs_pgio_header *hdr,
				 struct rpc_message *msg)
{
	msg->rpc_proc = &nfs3_procedures[NFS3PROC_READ];
	hdr->args.replen = NFS_SERVER(hdr->inode)->read_hdrsize;
}