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
typedef  int /*<<< orphan*/  u32 ;
struct xdr_stream {int dummy; } ;
struct compound_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_getattr (struct xdr_stream*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,struct compound_hdr*) ; 

__attribute__((used)) static void encode_getfattr_open(struct xdr_stream *xdr, const u32 *bitmask,
				 const u32 *open_bitmap,
				 struct compound_hdr *hdr)
{
	encode_getattr(xdr, open_bitmap, bitmask, 3, hdr);
}