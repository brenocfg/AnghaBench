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
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct file {int dummy; } ;
typedef  unsigned long ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {unsigned long io_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsnotify_access (struct file*) ; 
 int /*<<< orphan*/  nfsd_eof_on_read (struct file*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 TYPE_1__ nfsdstats ; 
 int /*<<< orphan*/  nfserrno (unsigned long) ; 
 int /*<<< orphan*/  trace_nfsd_read_err (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace_nfsd_read_io_done (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static __be32 nfsd_finish_read(struct svc_rqst *rqstp, struct svc_fh *fhp,
			       struct file *file, loff_t offset,
			       unsigned long *count, u32 *eof, ssize_t host_err)
{
	if (host_err >= 0) {
		nfsdstats.io_read += host_err;
		*eof = nfsd_eof_on_read(file, offset, host_err, *count);
		*count = host_err;
		fsnotify_access(file);
		trace_nfsd_read_io_done(rqstp, fhp, offset, *count);
		return 0;
	} else {
		trace_nfsd_read_err(rqstp, fhp, offset, host_err);
		return nfserrno(host_err);
	}
}