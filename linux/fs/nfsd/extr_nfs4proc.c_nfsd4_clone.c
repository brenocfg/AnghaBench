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
struct nfsd4_clone {int /*<<< orphan*/  cl_count; int /*<<< orphan*/  cl_dst_pos; int /*<<< orphan*/  cl_src_pos; int /*<<< orphan*/  cl_dst_stateid; int /*<<< orphan*/  cl_src_stateid; } ;
union nfsd4_op_u {struct nfsd4_clone clone; } ;
struct svc_rqst {int dummy; } ;
struct nfsd_file {int /*<<< orphan*/  nf_file; } ;
struct nfsd4_compound_state {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ nfsd4_clone_file_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_verify_copy (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *,struct nfsd_file**,int /*<<< orphan*/ *,struct nfsd_file**) ; 
 int /*<<< orphan*/  nfsd_file_put (struct nfsd_file*) ; 

__attribute__((used)) static __be32
nfsd4_clone(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_clone *clone = &u->clone;
	struct nfsd_file *src, *dst;
	__be32 status;

	status = nfsd4_verify_copy(rqstp, cstate, &clone->cl_src_stateid, &src,
				   &clone->cl_dst_stateid, &dst);
	if (status)
		goto out;

	status = nfsd4_clone_file_range(src->nf_file, clone->cl_src_pos,
			dst->nf_file, clone->cl_dst_pos, clone->cl_count);

	nfsd_file_put(dst);
	nfsd_file_put(src);
out:
	return status;
}