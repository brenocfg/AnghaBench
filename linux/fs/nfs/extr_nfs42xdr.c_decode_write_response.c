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
struct TYPE_2__ {int /*<<< orphan*/  verifier; void* committed; } ;
struct nfs42_write_res {TYPE_1__ verifier; int /*<<< orphan*/  count; int /*<<< orphan*/  stateid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  NFS4_STATEID_SIZE ; 
 void* be32_to_cpup (int /*<<< orphan*/ *) ; 
 int decode_opaque_fixed (struct xdr_stream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int decode_verifier (struct xdr_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_write_response(struct xdr_stream *xdr,
				 struct nfs42_write_res *res)
{
	__be32 *p;
	int status, count;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(!p))
		return -EIO;
	count = be32_to_cpup(p);
	if (count > 1)
		return -EREMOTEIO;
	else if (count == 1) {
		status = decode_opaque_fixed(xdr, &res->stateid,
				NFS4_STATEID_SIZE);
		if (unlikely(status))
			return -EIO;
	}
	p = xdr_inline_decode(xdr, 8 + 4);
	if (unlikely(!p))
		return -EIO;
	p = xdr_decode_hyper(p, &res->count);
	res->verifier.committed = be32_to_cpup(p);
	return decode_verifier(xdr, &res->verifier.verifier);
}