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
struct nfsd4_link {int /*<<< orphan*/  li_cinfo; int /*<<< orphan*/  li_namelen; int /*<<< orphan*/  li_name; } ;
union nfsd4_op_u {struct nfsd4_link link; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; int /*<<< orphan*/  save_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_link (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_link(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	   union nfsd4_op_u *u)
{
	struct nfsd4_link *link = &u->link;
	__be32 status;

	status = nfsd_link(rqstp, &cstate->current_fh,
			   link->li_name, link->li_namelen, &cstate->save_fh);
	if (!status)
		set_change_info(&link->li_cinfo, &cstate->current_fh);
	return status;
}