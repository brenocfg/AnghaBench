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
typedef  int /*<<< orphan*/  uint32_t ;
struct xdr_stream {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ decode_bitmap4 (struct xdr_stream*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_attr_bitmap(struct xdr_stream *xdr, uint32_t *bitmap)
{
	ssize_t ret;
	ret = decode_bitmap4(xdr, bitmap, 3);
	return ret < 0 ? ret : 0;
}