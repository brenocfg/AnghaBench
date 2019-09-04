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
typedef  scalar_t__ u32 ;
struct xdr_stream {int dummy; } ;
struct knfsd_fh {scalar_t__ fh_size; int /*<<< orphan*/  fh_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NFS4_FHSIZE ; 
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static void encode_nfs_fh4(struct xdr_stream *xdr, const struct knfsd_fh *fh)
{
	u32 length = fh->fh_size;
	__be32 *p;

	BUG_ON(length > NFS4_FHSIZE);
	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, &fh->fh_base, length);
}