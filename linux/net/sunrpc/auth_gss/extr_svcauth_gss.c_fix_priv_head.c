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
struct xdr_buf {scalar_t__ page_len; TYPE_1__* head; } ;
struct TYPE_2__ {int iov_len; } ;

/* Variables and functions */

__attribute__((used)) static void
fix_priv_head(struct xdr_buf *buf, int pad)
{
	if (buf->page_len == 0) {
		/* We need to adjust head and buf->len in tandem in this
		 * case to make svc_defer() work--it finds the original
		 * buffer start using buf->len - buf->head[0].iov_len. */
		buf->head[0].iov_len -= pad;
	}
}