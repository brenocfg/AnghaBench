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
struct svc_rqst {int /*<<< orphan*/  rq_auth_data; int /*<<< orphan*/  rq_argp; int /*<<< orphan*/  rq_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_rcu (struct svc_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rq_rcu_head ; 
 int /*<<< orphan*/  svc_release_buffer (struct svc_rqst*) ; 

void
svc_rqst_free(struct svc_rqst *rqstp)
{
	svc_release_buffer(rqstp);
	kfree(rqstp->rq_resp);
	kfree(rqstp->rq_argp);
	kfree(rqstp->rq_auth_data);
	kfree_rcu(rqstp, rq_rcu_head);
}