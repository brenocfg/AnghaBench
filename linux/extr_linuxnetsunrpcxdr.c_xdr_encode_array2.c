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
struct xdr_buf {unsigned long page_len; TYPE_2__* tail; TYPE_1__* head; } ;
struct xdr_array2_desc {unsigned long array_len; unsigned long elem_size; } ;
struct TYPE_4__ {unsigned long iov_len; } ;
struct TYPE_3__ {unsigned long iov_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int xdr_xcode_array2 (struct xdr_buf*,unsigned int,struct xdr_array2_desc*,int) ; 

int
xdr_encode_array2(struct xdr_buf *buf, unsigned int base,
		  struct xdr_array2_desc *desc)
{
	if ((unsigned long) base + 4 + desc->array_len * desc->elem_size >
	    buf->head->iov_len + buf->page_len + buf->tail->iov_len)
		return -EINVAL;

	return xdr_xcode_array2(buf, base, desc, 1);
}