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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS3_MAXNAMLEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  xdr_encode_opaque (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_filename3(struct xdr_stream *xdr,
			     const char *name, u32 length)
{
	__be32 *p;

	WARN_ON_ONCE(length > NFS3_MAXNAMLEN);
	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, name, length);
}