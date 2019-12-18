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
struct nfs_fsstat {int /*<<< orphan*/  afiles; int /*<<< orphan*/  ffiles; int /*<<< orphan*/  tfiles; int /*<<< orphan*/  abytes; int /*<<< orphan*/  fbytes; int /*<<< orphan*/  tbytes; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * xdr_decode_size3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_fsstat3resok(struct xdr_stream *xdr,
			       struct nfs_fsstat *result)
{
	__be32 *p;

	p = xdr_inline_decode(xdr, 8 * 6 + 4);
	if (unlikely(!p))
		return -EIO;
	p = xdr_decode_size3(p, &result->tbytes);
	p = xdr_decode_size3(p, &result->fbytes);
	p = xdr_decode_size3(p, &result->abytes);
	p = xdr_decode_size3(p, &result->tfiles);
	p = xdr_decode_size3(p, &result->ffiles);
	xdr_decode_size3(p, &result->afiles);
	/* ignore invarsec */
	return 0;
}