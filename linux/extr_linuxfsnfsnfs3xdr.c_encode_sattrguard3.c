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
struct nfs3_sattrargs {int /*<<< orphan*/  guardtime; scalar_t__ guard; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_encode_nfstime3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdr_one ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static void encode_sattrguard3(struct xdr_stream *xdr,
			       const struct nfs3_sattrargs *args)
{
	__be32 *p;

	if (args->guard) {
		p = xdr_reserve_space(xdr, 4 + 8);
		*p++ = xdr_one;
		xdr_encode_nfstime3(p, &args->guardtime);
	} else {
		p = xdr_reserve_space(xdr, 4);
		*p = xdr_zero;
	}
}