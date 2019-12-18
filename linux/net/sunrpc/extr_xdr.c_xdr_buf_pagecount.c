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
struct xdr_buf {int page_len; int page_base; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 

size_t
xdr_buf_pagecount(struct xdr_buf *buf)
{
	if (!buf->page_len)
		return 0;
	return (buf->page_base + buf->page_len + PAGE_SIZE - 1) >> PAGE_SHIFT;
}