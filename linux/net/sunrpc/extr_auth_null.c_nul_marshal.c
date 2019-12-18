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
struct rpc_task {int dummy; } ;
typedef  void* __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 void* rpc_auth_null ; 
 void** xdr_reserve_space (struct xdr_stream*,int) ; 
 void* xdr_zero ; 

__attribute__((used)) static int
nul_marshal(struct rpc_task *task, struct xdr_stream *xdr)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 * sizeof(*p));
	if (!p)
		return -EMSGSIZE;
	/* Credential */
	*p++ = rpc_auth_null;
	*p++ = xdr_zero;
	/* Verifier */
	*p++ = rpc_auth_null;
	*p   = xdr_zero;
	return 0;
}