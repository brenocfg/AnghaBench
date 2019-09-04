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
typedef  scalar_t__ u32 ;
struct xdr_buf {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rotate_left (struct xdr_buf*,unsigned int) ; 
 int /*<<< orphan*/  xdr_buf_subsegment (struct xdr_buf*,struct xdr_buf*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void rotate_left(u32 base, struct xdr_buf *buf, unsigned int shift)
{
	struct xdr_buf subbuf;

	xdr_buf_subsegment(buf, &subbuf, base, buf->len - base);
	_rotate_left(&subbuf, shift);
}