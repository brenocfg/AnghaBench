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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; } ;
struct svc_fh {int dummy; } ;
struct nfsd_file {struct file* nf_file; } ;
struct kvec {int dummy; } ;
struct file {TYPE_1__* f_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_2__ {scalar_t__ splice_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_READ ; 
 int /*<<< orphan*/  RQ_SPLICE_OK ; 
 scalar_t__ nfsd_file_acquire (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,struct nfsd_file**) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 
 scalar_t__ nfsd_readv (struct svc_rqst*,struct svc_fh*,struct file*,int /*<<< orphan*/ ,struct kvec*,int,unsigned long*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd_splice_read (struct svc_rqst*,struct svc_fh*,struct file*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_read_done (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_nfsd_read_start (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 

__be32 nfsd_read(struct svc_rqst *rqstp, struct svc_fh *fhp,
	loff_t offset, struct kvec *vec, int vlen, unsigned long *count,
	u32 *eof)
{
	struct nfsd_file	*nf;
	struct file *file;
	__be32 err;

	trace_nfsd_read_start(rqstp, fhp, offset, *count);
	err = nfsd_file_acquire(rqstp, fhp, NFSD_MAY_READ, &nf);
	if (err)
		return err;

	file = nf->nf_file;
	if (file->f_op->splice_read && test_bit(RQ_SPLICE_OK, &rqstp->rq_flags))
		err = nfsd_splice_read(rqstp, fhp, file, offset, count, eof);
	else
		err = nfsd_readv(rqstp, fhp, file, offset, vec, vlen, count, eof);

	nfsd_file_put(nf);

	trace_nfsd_read_done(rqstp, fhp, offset, *count);

	return err;
}