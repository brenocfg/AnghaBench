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
struct xdr_stream {int dummy; } ;
struct rpc_rqst {int dummy; } ;
struct nfs_pgio_res {int /*<<< orphan*/  op_status; int /*<<< orphan*/  fattr; TYPE_1__* verf; } ;
struct TYPE_2__ {int /*<<< orphan*/  committed; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FILE_SYNC ; 
 int decode_attrstat (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 

__attribute__((used)) static int nfs2_xdr_dec_writeres(struct rpc_rqst *req, struct xdr_stream *xdr,
				 void *data)
{
	struct nfs_pgio_res *result = data;

	/* All NFSv2 writes are "file sync" writes */
	result->verf->committed = NFS_FILE_SYNC;
	return decode_attrstat(xdr, result->fattr, &result->op_status,
			rpc_rqst_userns(req));
}