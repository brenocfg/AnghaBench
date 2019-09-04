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
typedef  int /*<<< orphan*/  u8 ;
struct xdr_buf {unsigned int len; TYPE_1__* head; } ;
struct TYPE_2__ {scalar_t__ iov_len; int /*<<< orphan*/ * iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int GSS_KRB5_MAX_SLACK_NEEDED ; 
 unsigned int RPC_MAX_AUTH_SIZE ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int
xdr_extend_head(struct xdr_buf *buf, unsigned int base, unsigned int shiftlen)
{
	u8 *p;

	if (shiftlen == 0)
		return 0;

	BUILD_BUG_ON(GSS_KRB5_MAX_SLACK_NEEDED > RPC_MAX_AUTH_SIZE);
	BUG_ON(shiftlen > RPC_MAX_AUTH_SIZE);

	p = buf->head[0].iov_base + base;

	memmove(p + shiftlen, p, buf->head[0].iov_len - base);

	buf->head[0].iov_len += shiftlen;
	buf->len += shiftlen;

	return 0;
}