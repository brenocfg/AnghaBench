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
struct nfsd4_op {scalar_t__ status; size_t opnum; } ;
struct nfsd4_compoundargs {scalar_t__ minorversion; int opcnt; struct nfsd4_op* ops; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int op_flags; } ;

/* Variables and functions */
 int ALLOWED_AS_FIRST_OP ; 
 size_t OP_SEQUENCE ; 
 int /*<<< orphan*/  nfs_ok ; 
 TYPE_1__* nfsd4_ops ; 
 int /*<<< orphan*/  nfserr_not_only_op ; 
 scalar_t__ nfserr_op_illegal ; 
 int /*<<< orphan*/  nfserr_op_not_in_session ; 

__attribute__((used)) static __be32 nfs41_check_op_ordering(struct nfsd4_compoundargs *args)
{
	struct nfsd4_op *first_op = &args->ops[0];

	/* These ordering requirements don't apply to NFSv4.0: */
	if (args->minorversion == 0)
		return nfs_ok;
	/* This is weird, but OK, not our problem: */
	if (args->opcnt == 0)
		return nfs_ok;
	if (first_op->status == nfserr_op_illegal)
		return nfs_ok;
	if (!(nfsd4_ops[first_op->opnum].op_flags & ALLOWED_AS_FIRST_OP))
		return nfserr_op_not_in_session;
	if (first_op->opnum == OP_SEQUENCE)
		return nfs_ok;
	/*
	 * So first_op is something allowed outside a session, like
	 * EXCHANGE_ID; but then it has to be the only op in the
	 * compound:
	 */
	if (args->opcnt != 1)
		return nfserr_not_only_op;
	return nfs_ok;
}