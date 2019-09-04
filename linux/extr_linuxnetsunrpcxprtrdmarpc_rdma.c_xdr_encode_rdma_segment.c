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
struct rpcrdma_mr {int /*<<< orphan*/  mr_offset; int /*<<< orphan*/  mr_length; int /*<<< orphan*/  mr_handle; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xdr_encode_rdma_segment(__be32 *iptr, struct rpcrdma_mr *mr)
{
	*iptr++ = cpu_to_be32(mr->mr_handle);
	*iptr++ = cpu_to_be32(mr->mr_length);
	xdr_encode_hyper(iptr, mr->mr_offset);
}