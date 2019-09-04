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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ xdr_stream_encode_uint32_array (struct xdr_stream*,scalar_t__ const*,size_t) ; 

__attribute__((used)) static ssize_t xdr_encode_bitmap4(struct xdr_stream *xdr,
		const __u32 *bitmap, size_t len)
{
	ssize_t ret;

	/* Trim empty words */
	while (len > 0 && bitmap[len-1] == 0)
		len--;
	ret = xdr_stream_encode_uint32_array(xdr, bitmap, len);
	if (WARN_ON_ONCE(ret < 0))
		return ret;
	return len;
}