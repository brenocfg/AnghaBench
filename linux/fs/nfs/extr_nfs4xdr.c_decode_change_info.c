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
struct nfs4_change_info {int /*<<< orphan*/  after; int /*<<< orphan*/  before; int /*<<< orphan*/  atomic; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_change_info(struct xdr_stream *xdr, struct nfs4_change_info *cinfo)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 20);
	if (unlikely(!p))
		return -EIO;
	cinfo->atomic = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &cinfo->before);
	xdr_decode_hyper(p, &cinfo->after);
	return 0;
}