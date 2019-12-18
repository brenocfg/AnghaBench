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
struct xdr_buf {size_t len; TYPE_1__* head; } ;
struct TYPE_2__ {size_t iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline void rpcrdma_set_xdrlen(struct xdr_buf *xdr, size_t len)
{
	xdr->head[0].iov_len = len;
	xdr->len = len;
}