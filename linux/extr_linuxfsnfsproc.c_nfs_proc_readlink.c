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
struct rpc_message {struct nfs_readlinkargs* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct page {int dummy; } ;
struct nfs_readlinkargs {unsigned int pgbase; unsigned int pglen; struct page** pages; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 size_t NFSPROC_READLINK ; 
 int /*<<< orphan*/  NFS_CLIENT (struct inode*) ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_proc_readlink(struct inode *inode, struct page *page,
		unsigned int pgbase, unsigned int pglen)
{
	struct nfs_readlinkargs	args = {
		.fh		= NFS_FH(inode),
		.pgbase		= pgbase,
		.pglen		= pglen,
		.pages		= &page
	};
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_READLINK],
		.rpc_argp	= &args,
	};
	int			status;

	dprintk("NFS call  readlink\n");
	status = rpc_call_sync(NFS_CLIENT(inode), &msg, 0);
	dprintk("NFS reply readlink: %d\n", status);
	return status;
}