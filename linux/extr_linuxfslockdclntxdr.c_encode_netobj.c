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
typedef  int /*<<< orphan*/  u8 ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int const) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static void encode_netobj(struct xdr_stream *xdr,
			  const u8 *data, const unsigned int length)
{
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, data, length);
}