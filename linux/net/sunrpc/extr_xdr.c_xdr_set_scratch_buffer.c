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
struct TYPE_2__ {size_t iov_len; void* iov_base; } ;
struct xdr_stream {TYPE_1__ scratch; } ;

/* Variables and functions */

void xdr_set_scratch_buffer(struct xdr_stream *xdr, void *buf, size_t buflen)
{
	xdr->scratch.iov_base = buf;
	xdr->scratch.iov_len = buflen;
}