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
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int decode_attrstat (struct xdr_stream*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_rqst_userns (struct rpc_rqst*) ; 

__attribute__((used)) static int nfs2_xdr_dec_attrstat(struct rpc_rqst *req, struct xdr_stream *xdr,
				 void *result)
{
	return decode_attrstat(xdr, result, NULL, rpc_rqst_userns(req));
}