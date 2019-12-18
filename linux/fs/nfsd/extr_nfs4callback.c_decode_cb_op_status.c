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
typedef  int u32 ;
struct xdr_stream {int dummy; } ;
typedef  enum nfs_cb_opnum4 { ____Placeholder_nfs_cb_opnum4 } nfs_cb_opnum4 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int nfs_cb_stat_to_errno (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_cb_op_status(struct xdr_stream *xdr,
			       enum nfs_cb_opnum4 expected, int *status)
{
	__be32 *p;
	u32 op;

	p = xdr_inline_decode(xdr, 4 + 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	op = be32_to_cpup(p++);
	if (unlikely(op != expected))
		goto out_unexpected;
	*status = nfs_cb_stat_to_errno(be32_to_cpup(p));
	return 0;
out_overflow:
	return -EIO;
out_unexpected:
	dprintk("NFSD: Callback server returned operation %d but "
		"we issued a request for %d\n", op, expected);
	return -EIO;
}