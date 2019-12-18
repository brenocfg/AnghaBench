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
struct nlm_cookie {int len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int NLM_MAXCOOKIELEN ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_inline_decode (struct xdr_stream*,int) ; 

__attribute__((used)) static int decode_cookie(struct xdr_stream *xdr,
			     struct nlm_cookie *cookie)
{
	u32 length;
	__be32 *p;

	p = xdr_inline_decode(xdr, 4);
	if (unlikely(p == NULL))
		goto out_overflow;
	length = be32_to_cpup(p++);
	/* apparently HPUX can return empty cookies */
	if (length == 0)
		goto out_hpux;
	if (length > NLM_MAXCOOKIELEN)
		goto out_size;
	p = xdr_inline_decode(xdr, length);
	if (unlikely(p == NULL))
		goto out_overflow;
	cookie->len = length;
	memcpy(cookie->data, p, length);
	return 0;
out_hpux:
	cookie->len = 4;
	memset(cookie->data, 0, 4);
	return 0;
out_size:
	dprintk("NFS: returned cookie was too long: %u\n", length);
	return -EIO;
out_overflow:
	return -EIO;
}