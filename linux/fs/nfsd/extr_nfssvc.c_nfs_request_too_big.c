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
struct TYPE_2__ {scalar_t__ len; } ;
struct svc_rqst {scalar_t__ rq_prog; int rq_vers; TYPE_1__ rq_arg; } ;
struct svc_procedure {scalar_t__ pc_xdrressize; } ;

/* Variables and functions */
 scalar_t__ NFS_PROGRAM ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ XDR_QUADLEN (scalar_t__) ; 

__attribute__((used)) static bool nfs_request_too_big(struct svc_rqst *rqstp,
				const struct svc_procedure *proc)
{
	/*
	 * The ACL code has more careful bounds-checking and is not
	 * susceptible to this problem:
	 */
	if (rqstp->rq_prog != NFS_PROGRAM)
		return false;
	/*
	 * Ditto NFSv4 (which can in theory have argument and reply both
	 * more than a page):
	 */
	if (rqstp->rq_vers >= 4)
		return false;
	/* The reply will be small, we're OK: */
	if (proc->pc_xdrressize > 0 &&
	    proc->pc_xdrressize < XDR_QUADLEN(PAGE_SIZE))
		return false;

	return rqstp->rq_arg.len > PAGE_SIZE;
}