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
struct xdr_stream {int dummy; } ;
struct nfs_lock_res {int /*<<< orphan*/  lock_seqid; int /*<<< orphan*/ * open_seqid; int /*<<< orphan*/  stateid; } ;

/* Variables and functions */
 int EIO ; 
 int NFS4ERR_DENIED ; 
 int /*<<< orphan*/  OP_LOCK ; 
 int decode_lock_denied (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int decode_lock_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 int decode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_increment_lock_seqid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_increment_open_seqid (int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int decode_lock(struct xdr_stream *xdr, struct nfs_lock_res *res)
{
	int status;

	status = decode_op_hdr(xdr, OP_LOCK);
	if (status == -EIO)
		goto out;
	if (status == 0) {
		status = decode_lock_stateid(xdr, &res->stateid);
		if (unlikely(status))
			goto out;
	} else if (status == -NFS4ERR_DENIED)
		status = decode_lock_denied(xdr, NULL);
	if (res->open_seqid != NULL)
		nfs_increment_open_seqid(status, res->open_seqid);
	nfs_increment_lock_seqid(status, res->lock_seqid);
out:
	return status;
}