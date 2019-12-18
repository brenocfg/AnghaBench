#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {scalar_t__ tk_status; } ;
struct TYPE_10__ {scalar_t__ stable; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {TYPE_4__* verf; int /*<<< orphan*/  count; } ;
struct nfs_pgio_header {TYPE_3__ args; TYPE_2__ res; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_14__ {int /*<<< orphan*/  cache_validity; } ;
struct TYPE_13__ {int (* write_done ) (struct rpc_task*,struct nfs_pgio_header*) ;} ;
struct TYPE_12__ {TYPE_1__* nfs_client; } ;
struct TYPE_11__ {scalar_t__ committed; } ;
struct TYPE_8__ {int /*<<< orphan*/  cl_hostname; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  NFSIOS_SERVERWRITTENBYTES ; 
 TYPE_7__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_INVALID_OTHER ; 
 TYPE_6__* NFS_PROTO (struct inode*) ; 
 TYPE_5__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int jiffies ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_should_remove_suid (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rpc_task*,struct nfs_pgio_header*) ; 
 scalar_t__ time_before (unsigned long,int) ; 
 int /*<<< orphan*/  trace_nfs_writeback_done (struct inode*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static int nfs_writeback_done(struct rpc_task *task,
			      struct nfs_pgio_header *hdr,
			      struct inode *inode)
{
	int status;

	/*
	 * ->write_done will attempt to use post-op attributes to detect
	 * conflicting writes by other clients.  A strict interpretation
	 * of close-to-open would allow us to continue caching even if
	 * another writer had changed the file, but some applications
	 * depend on tighter cache coherency when writing.
	 */
	status = NFS_PROTO(inode)->write_done(task, hdr);
	if (status != 0)
		return status;

	nfs_add_stats(inode, NFSIOS_SERVERWRITTENBYTES, hdr->res.count);
	trace_nfs_writeback_done(inode, task->tk_status,
				 hdr->args.offset, hdr->res.verf);

	if (hdr->res.verf->committed < hdr->args.stable &&
	    task->tk_status >= 0) {
		/* We tried a write call, but the server did not
		 * commit data to stable storage even though we
		 * requested it.
		 * Note: There is a known bug in Tru64 < 5.0 in which
		 *	 the server reports NFS_DATA_SYNC, but performs
		 *	 NFS_FILE_SYNC. We therefore implement this checking
		 *	 as a dprintk() in order to avoid filling syslog.
		 */
		static unsigned long    complain;

		/* Note this will print the MDS for a DS write */
		if (time_before(complain, jiffies)) {
			dprintk("NFS:       faulty NFS server %s:"
				" (committed = %d) != (stable = %d)\n",
				NFS_SERVER(inode)->nfs_client->cl_hostname,
				hdr->res.verf->committed, hdr->args.stable);
			complain = jiffies + 300 * HZ;
		}
	}

	/* Deal with the suid/sgid bit corner case */
	if (nfs_should_remove_suid(inode)) {
		spin_lock(&inode->i_lock);
		NFS_I(inode)->cache_validity |= NFS_INO_INVALID_OTHER;
		spin_unlock(&inode->i_lock);
	}
	return 0;
}