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
struct svc_xprt {int /*<<< orphan*/  xpt_bc_xprt; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_CALL ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_msg ; 
 scalar_t__ xdr_zero ; 

__attribute__((used)) static bool svc_rdma_is_backchannel_reply(struct svc_xprt *xprt,
					  __be32 *rdma_resp)
{
	__be32 *p;

	if (!xprt->xpt_bc_xprt)
		return false;

	p = rdma_resp + 3;
	if (*p++ != rdma_msg)
		return false;

	if (*p++ != xdr_zero)
		return false;
	if (*p++ != xdr_zero)
		return false;
	if (*p++ != xdr_zero)
		return false;

	/* XID sanity */
	if (*p++ != *rdma_resp)
		return false;
	/* call direction */
	if (*p == cpu_to_be32(RPC_CALL))
		return false;

	return true;
}