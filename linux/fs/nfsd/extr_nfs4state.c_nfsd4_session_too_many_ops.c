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
struct svc_rqst {struct nfsd4_compoundargs* rq_argp; } ;
struct TYPE_2__ {scalar_t__ maxops; } ;
struct nfsd4_session {TYPE_1__ se_fchannel; } ;
struct nfsd4_compoundargs {scalar_t__ opcnt; } ;

/* Variables and functions */

__attribute__((used)) static bool nfsd4_session_too_many_ops(struct svc_rqst *rqstp, struct nfsd4_session *session)
{
	struct nfsd4_compoundargs *args = rqstp->rq_argp;

	return args->opcnt > session->se_fchannel.maxops;
}