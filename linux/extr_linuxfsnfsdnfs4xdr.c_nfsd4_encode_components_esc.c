#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {TYPE_1__* buf; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  write_bytes_to_xdr_buf (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xdr_encode_opaque (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * xdr_reserve_space (struct xdr_stream*,int) ; 

__attribute__((used)) static __be32 nfsd4_encode_components_esc(struct xdr_stream *xdr, char sep,
					  char *components, char esc_enter,
					  char esc_exit)
{
	__be32 *p;
	__be32 pathlen;
	int pathlen_offset;
	int strlen, count=0;
	char *str, *end, *next;

	dprintk("nfsd4_encode_components(%s)\n", components);

	pathlen_offset = xdr->buf->len;
	p = xdr_reserve_space(xdr, 4);
	if (!p)
		return nfserr_resource;
	p++; /* We will fill this in with @count later */

	end = str = components;
	while (*end) {
		bool found_esc = false;

		/* try to parse as esc_start, ..., esc_end, sep */
		if (*str == esc_enter) {
			for (; *end && (*end != esc_exit); end++)
				/* find esc_exit or end of string */;
			next = end + 1;
			if (*end && (!*next || *next == sep)) {
				str++;
				found_esc = true;
			}
		}

		if (!found_esc)
			for (; *end && (*end != sep); end++)
				/* find sep or end of string */;

		strlen = end - str;
		if (strlen) {
			p = xdr_reserve_space(xdr, strlen + 4);
			if (!p)
				return nfserr_resource;
			p = xdr_encode_opaque(p, str, strlen);
			count++;
		}
		else
			end++;
		if (found_esc)
			end = next;

		str = end;
	}
	pathlen = htonl(count);
	write_bytes_to_xdr_buf(xdr->buf, pathlen_offset, &pathlen, 4);
	return 0;
}