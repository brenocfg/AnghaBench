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
struct rpc_rqst {int /*<<< orphan*/  rq_snd_buf; } ;
typedef  int /*<<< orphan*/  (* kxdreproc_t ) (struct rpc_rqst*,struct xdr_stream*,void*) ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_init_encode (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gss_wrap_req_encode(kxdreproc_t encode, struct rpc_rqst *rqstp,
				__be32 *p, void *obj)
{
	struct xdr_stream xdr;

	xdr_init_encode(&xdr, &rqstp->rq_snd_buf, p);
	encode(rqstp, &xdr, obj);
}