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
typedef  void* uint32_t ;
struct xdr_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_buf (struct xdr_stream*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 decode_bitmap(struct xdr_stream *xdr, uint32_t *bitmap)
{
	__be32 *p;
	unsigned int attrlen;

	p = read_buf(xdr, 4);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE);
	attrlen = ntohl(*p);
	p = read_buf(xdr, attrlen << 2);
	if (unlikely(p == NULL))
		return htonl(NFS4ERR_RESOURCE);
	if (likely(attrlen > 0))
		bitmap[0] = ntohl(*p++);
	if (attrlen > 1)
		bitmap[1] = ntohl(*p);
	return 0;
}