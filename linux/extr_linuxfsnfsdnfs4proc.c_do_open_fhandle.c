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
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct TYPE_2__ {int ia_valid; scalar_t__ ia_size; } ;
struct nfsd4_open {int op_truncate; scalar_t__ op_claim_type; TYPE_1__ op_iattr; int /*<<< orphan*/  op_cinfo; } ;
struct nfsd4_compound_state {struct svc_fh current_fh; } ;
struct nfsd4_change_info {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ATTR_SIZE ; 
 scalar_t__ NFS4_OPEN_CLAIM_DELEG_CUR_FH ; 
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int /*<<< orphan*/  do_open_permission (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsd4_set_open_owner_reply_cache (struct nfsd4_compound_state*,struct nfsd4_open*,struct svc_fh*) ; 

__attribute__((used)) static __be32
do_open_fhandle(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate, struct nfsd4_open *open)
{
	struct svc_fh *current_fh = &cstate->current_fh;
	__be32 status;
	int accmode = 0;

	/* We don't know the target directory, and therefore can not
	* set the change info
	*/

	memset(&open->op_cinfo, 0, sizeof(struct nfsd4_change_info));

	nfsd4_set_open_owner_reply_cache(cstate, open, current_fh);

	open->op_truncate = (open->op_iattr.ia_valid & ATTR_SIZE) &&
		(open->op_iattr.ia_size == 0);
	/*
	 * In the delegation case, the client is telling us about an
	 * open that it *already* performed locally, some time ago.  We
	 * should let it succeed now if possible.
	 *
	 * In the case of a CLAIM_FH open, on the other hand, the client
	 * may be counting on us to enforce permissions (the Linux 4.1
	 * client uses this for normal opens, for example).
	 */
	if (open->op_claim_type == NFS4_OPEN_CLAIM_DELEG_CUR_FH)
		accmode = NFSD_MAY_OWNER_OVERRIDE;

	status = do_open_permission(rqstp, current_fh, open, accmode);

	return status;
}