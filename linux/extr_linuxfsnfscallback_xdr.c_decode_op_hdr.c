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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE_HDR ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_buf (struct xdr_stream*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 decode_op_hdr(struct xdr_stream *xdr, unsigned int *op)
{
	__be32 *p;
	p = read_buf(xdr, 4);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE_HDR);
	*op = ntohl(*p);
	return 0;
}