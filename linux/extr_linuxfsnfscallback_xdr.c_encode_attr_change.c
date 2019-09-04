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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int const FATTR4_WORD0_CHANGE ; 
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 encode_attr_change(struct xdr_stream *xdr, const uint32_t *bitmap, uint64_t change)
{
	__be32 *p;

	if (!(bitmap[0] & FATTR4_WORD0_CHANGE))
		return 0;
	p = xdr_reserve_space(xdr, 8);
	if (unlikely(!p))
		return htonl(NFS4ERR_RESOURCE);
	p = xdr_encode_hyper(p, change);
	return 0;
}