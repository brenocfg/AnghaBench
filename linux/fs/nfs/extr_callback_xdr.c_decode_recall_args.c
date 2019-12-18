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
struct svc_rqst {int dummy; } ;
struct cb_recallargs {int /*<<< orphan*/  fh; int /*<<< orphan*/  truncate; int /*<<< orphan*/  stateid; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 scalar_t__ decode_delegation_stateid (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ decode_fh (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__* xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 decode_recall_args(struct svc_rqst *rqstp,
		struct xdr_stream *xdr, void *argp)
{
	struct cb_recallargs *args = argp;
	__be32 *p;
	__be32 status;

	status = decode_delegation_stateid(xdr, &args->stateid);
	if (unlikely(status != 0))
		return status;
	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE);
	args->truncate = ntohl(*p);
	return decode_fh(xdr, &args->fh);
}