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
struct nfs_pgio_res {scalar_t__ count; scalar_t__ eof; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 
 scalar_t__ xdr_read_pages (struct xdr_stream*,scalar_t__) ; 

__attribute__((used)) static int decode_read3resok(struct xdr_stream *xdr,
			     struct nfs_pgio_res *result)
{
	u32 eof, count, ocount, recvd;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4 + 4 + 4);
	if (unlikely(!p))
		return -EIO;
	count = be32_to_cpup(p++);
	eof = be32_to_cpup(p++);
	ocount = be32_to_cpup(p++);
	if (unlikely(ocount != count))
		goto out_mismatch;
	recvd = xdr_read_pages(xdr, count);
	if (unlikely(count > recvd))
		goto out_cheating;
out:
	result->eof = eof;
	result->count = count;
	return count;
out_mismatch:
	dprintk("NFS: READ count doesn't match length of opaque: "
		"count %u != ocount %u\n", count, ocount);
	return -EIO;
out_cheating:
	dprintk("NFS: server cheating in read result: "
		"count %u > recvd %u\n", count, recvd);
	count = recvd;
	eof = 0;
	goto out;
}