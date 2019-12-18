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
struct user_namespace {int dummy; } ;
struct svc_rqst {TYPE_1__* rq_xprt; } ;
struct cred {struct user_namespace* user_ns; } ;
struct TYPE_2__ {struct cred* xpt_cred; } ;

/* Variables and functions */
 struct user_namespace init_user_ns ; 

__attribute__((used)) static inline struct user_namespace *
nfsd_user_namespace(const struct svc_rqst *rqstp)
{
	const struct cred *cred = rqstp->rq_xprt->xpt_cred;
	return cred ? cred->user_ns : &init_user_ns;
}