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
struct TYPE_2__ {int /*<<< orphan*/  wr_verifier; int /*<<< orphan*/  wr_stable_how; scalar_t__ wr_bytes_written; } ;
struct nfsd4_copy {int cp_synchronous; TYPE_1__ cp_res; int /*<<< orphan*/  cp_count; int /*<<< orphan*/  cp_dst_pos; int /*<<< orphan*/  cp_src_pos; int /*<<< orphan*/  cp_dst_stateid; int /*<<< orphan*/  cp_src_stateid; } ;
union nfsd4_op_u {struct nfsd4_copy copy; } ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_UNSTABLE ; 
 int /*<<< orphan*/  SVC_NET (struct svc_rqst*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  gen_boot_verifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_verify_copy (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ *,struct file**,int /*<<< orphan*/ *,struct file**) ; 
 scalar_t__ nfsd_copy_file_range (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserrno (scalar_t__) ; 

__attribute__((used)) static __be32
nfsd4_copy(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		union nfsd4_op_u *u)
{
	struct nfsd4_copy *copy = &u->copy;
	struct file *src, *dst;
	__be32 status;
	ssize_t bytes;

	status = nfsd4_verify_copy(rqstp, cstate, &copy->cp_src_stateid, &src,
				   &copy->cp_dst_stateid, &dst);
	if (status)
		goto out;

	bytes = nfsd_copy_file_range(src, copy->cp_src_pos,
			dst, copy->cp_dst_pos, copy->cp_count);

	if (bytes < 0)
		status = nfserrno(bytes);
	else {
		copy->cp_res.wr_bytes_written = bytes;
		copy->cp_res.wr_stable_how = NFS_UNSTABLE;
		copy->cp_synchronous = 1;
		gen_boot_verifier(&copy->cp_res.wr_verifier, SVC_NET(rqstp));
		status = nfs_ok;
	}

	fput(src);
	fput(dst);
out:
	return status;
}