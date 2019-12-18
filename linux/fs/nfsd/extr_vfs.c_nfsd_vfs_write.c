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
struct svc_rqst {int rq_vers; int /*<<< orphan*/  rq_flags; } ;
struct svc_fh {struct svc_export* fh_export; } ;
struct svc_export {int dummy; } ;
struct kvec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  rwf_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {unsigned int flags; } ;
struct TYPE_3__ {unsigned long io_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_ISSYNC (struct svc_export*) ; 
 scalar_t__ EX_WGATHER (struct svc_export*) ; 
 int NFS_UNSTABLE ; 
 unsigned int PF_LESS_THROTTLE ; 
 int /*<<< orphan*/  RQ_LOCAL ; 
 int /*<<< orphan*/  RWF_SYNC ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  WRITE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_restore_flags (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fsnotify_modify (struct file*) ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,unsigned long) ; 
 int /*<<< orphan*/  net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  nfsd_reset_boot_verifier (int /*<<< orphan*/ ) ; 
 TYPE_1__ nfsdstats ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_write_err (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_nfsd_write_io_done (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_nfsd_write_opened (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 
 int vfs_iter_write (struct file*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wait_for_concurrent_writes (struct file*) ; 

__be32
nfsd_vfs_write(struct svc_rqst *rqstp, struct svc_fh *fhp, struct file *file,
				loff_t offset, struct kvec *vec, int vlen,
				unsigned long *cnt, int stable)
{
	struct svc_export	*exp;
	struct iov_iter		iter;
	__be32			nfserr;
	int			host_err;
	int			use_wgather;
	loff_t			pos = offset;
	unsigned int		pflags = current->flags;
	rwf_t			flags = 0;

	trace_nfsd_write_opened(rqstp, fhp, offset, *cnt);

	if (test_bit(RQ_LOCAL, &rqstp->rq_flags))
		/*
		 * We want less throttling in balance_dirty_pages()
		 * and shrink_inactive_list() so that nfs to
		 * localhost doesn't cause nfsd to lock up due to all
		 * the client's dirty pages or its congested queue.
		 */
		current->flags |= PF_LESS_THROTTLE;

	exp = fhp->fh_export;
	use_wgather = (rqstp->rq_vers == 2) && EX_WGATHER(exp);

	if (!EX_ISSYNC(exp))
		stable = NFS_UNSTABLE;

	if (stable && !use_wgather)
		flags |= RWF_SYNC;

	iov_iter_kvec(&iter, WRITE, vec, vlen, *cnt);
	host_err = vfs_iter_write(file, &iter, &pos, flags);
	if (host_err < 0)
		goto out_nfserr;
	nfsdstats.io_write += *cnt;
	fsnotify_modify(file);

	if (stable && use_wgather) {
		host_err = wait_for_concurrent_writes(file);
		if (host_err < 0)
			nfsd_reset_boot_verifier(net_generic(SVC_NET(rqstp),
						 nfsd_net_id));
	}

out_nfserr:
	if (host_err >= 0) {
		trace_nfsd_write_io_done(rqstp, fhp, offset, *cnt);
		nfserr = nfs_ok;
	} else {
		trace_nfsd_write_err(rqstp, fhp, offset, host_err);
		nfserr = nfserrno(host_err);
	}
	if (test_bit(RQ_LOCAL, &rqstp->rq_flags))
		current_restore_flags(pflags, PF_LESS_THROTTLE);
	return nfserr;
}