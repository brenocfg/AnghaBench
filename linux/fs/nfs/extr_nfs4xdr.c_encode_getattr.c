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
struct compound_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP_GETATTR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  decode_getattr_maxsz ; 
 int /*<<< orphan*/  encode_op_hdr (struct xdr_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct compound_hdr*) ; 
 size_t mask_bitmap4 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int nfs4_fattr_bitmap_maxsz ; 
 int /*<<< orphan*/  xdr_encode_bitmap4 (struct xdr_stream*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void encode_getattr(struct xdr_stream *xdr,
		const __u32 *bitmap, const __u32 *mask, size_t len,
		struct compound_hdr *hdr)
{
	__u32 masked_bitmap[nfs4_fattr_bitmap_maxsz];

	encode_op_hdr(xdr, OP_GETATTR, decode_getattr_maxsz, hdr);
	if (mask) {
		if (WARN_ON_ONCE(len > ARRAY_SIZE(masked_bitmap)))
			len = ARRAY_SIZE(masked_bitmap);
		len = mask_bitmap4(bitmap, mask, masked_bitmap, len);
		bitmap = masked_bitmap;
	}
	xdr_encode_bitmap4(xdr, bitmap, len);
}