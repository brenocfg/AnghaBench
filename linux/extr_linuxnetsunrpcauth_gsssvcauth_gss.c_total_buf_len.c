#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_buf {int page_len; TYPE_2__* tail; TYPE_1__* head; } ;
struct TYPE_4__ {int iov_len; } ;
struct TYPE_3__ {int iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline int
total_buf_len(struct xdr_buf *buf)
{
	return buf->head[0].iov_len + buf->page_len + buf->tail[0].iov_len;
}