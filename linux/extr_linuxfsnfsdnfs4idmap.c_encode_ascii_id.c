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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfserr_resource ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 encode_ascii_id(struct xdr_stream *xdr, u32 id)
{
	char buf[11];
	int len;
	__be32 *p;

	len = sprintf(buf, "%u", id);
	p = xdr_reserve_space(xdr, len + 4);
	if (!p)
		return nfserr_resource;
	p = xdr_encode_opaque(p, buf, len);
	return 0;
}