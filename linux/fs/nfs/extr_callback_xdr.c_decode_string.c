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
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4ERR_RESOURCE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 unsigned int xdr_stream_decode_opaque_inline (struct xdr_stream*,void**,size_t) ; 

__attribute__((used)) static __be32 decode_string(struct xdr_stream *xdr, unsigned int *len,
		const char **str, size_t maxlen)
{
	ssize_t err;

	err = xdr_stream_decode_opaque_inline(xdr, (void **)str, maxlen);
	if (err < 0)
		return cpu_to_be32(NFS4ERR_RESOURCE);
	*len = err;
	return 0;
}