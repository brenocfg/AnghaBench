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
struct svc_rqst {scalar_t__ rq_prog; int rq_vers; } ;

/* Variables and functions */
 scalar_t__ NFS_PROGRAM ; 

__attribute__((used)) static inline int nfsd_v4client(struct svc_rqst *rq)
{
	return rq->rq_prog == NFS_PROGRAM && rq->rq_vers == 4;
}