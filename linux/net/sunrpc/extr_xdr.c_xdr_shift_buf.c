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
struct xdr_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xdr_shrink_bufhead (struct xdr_buf*,size_t) ; 

void
xdr_shift_buf(struct xdr_buf *buf, size_t len)
{
	xdr_shrink_bufhead(buf, len);
}