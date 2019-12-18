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
typedef  unsigned int uint32_t ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 unsigned int FATTR4_WORD0_RDATTR_ERROR ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_attr_error(struct xdr_stream *xdr, uint32_t *bitmap, int32_t *res)
{
	__be32 *p;

	if (unlikely(bitmap[0] & (FATTR4_WORD0_RDATTR_ERROR - 1U)))
		return -EIO;
	if (likely(bitmap[0] & FATTR4_WORD0_RDATTR_ERROR)) {
		p = xdr_inline_decode(xdr, 4);
		if (unlikely(!p))
			return -EIO;
		bitmap[0] &= ~FATTR4_WORD0_RDATTR_ERROR;
		*res = -be32_to_cpup(p);
	}
	return 0;
}