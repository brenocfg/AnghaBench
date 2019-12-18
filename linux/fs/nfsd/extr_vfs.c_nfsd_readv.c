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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct kvec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int /*<<< orphan*/ ,struct kvec*,int,unsigned long) ; 
 int /*<<< orphan*/  nfsd_finish_read (struct svc_rqst*,struct svc_fh*,struct file*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_nfsd_read_vector (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vfs_iter_read (struct file*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__be32 nfsd_readv(struct svc_rqst *rqstp, struct svc_fh *fhp,
		  struct file *file, loff_t offset,
		  struct kvec *vec, int vlen, unsigned long *count,
		  u32 *eof)
{
	struct iov_iter iter;
	loff_t ppos = offset;
	ssize_t host_err;

	trace_nfsd_read_vector(rqstp, fhp, offset, *count);
	iov_iter_kvec(&iter, READ, vec, vlen, *count);
	host_err = vfs_iter_read(file, &iter, &ppos, 0);
	return nfsd_finish_read(rqstp, fhp, file, offset, count, eof, host_err);
}