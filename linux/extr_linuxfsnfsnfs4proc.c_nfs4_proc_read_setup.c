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
struct TYPE_4__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  seq_args; } ;
struct nfs_pgio_header {TYPE_2__ res; TYPE_1__ args; scalar_t__ pgio_done_cb; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 size_t NFSPROC4_CLNT_READ ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs4_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 scalar_t__ nfs4_read_done_cb ; 

__attribute__((used)) static void nfs4_proc_read_setup(struct nfs_pgio_header *hdr,
				 struct rpc_message *msg)
{
	hdr->timestamp   = jiffies;
	if (!hdr->pgio_done_cb)
		hdr->pgio_done_cb = nfs4_read_done_cb;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_READ];
	nfs4_init_sequence(&hdr->args.seq_args, &hdr->res.seq_res, 0, 0);
}