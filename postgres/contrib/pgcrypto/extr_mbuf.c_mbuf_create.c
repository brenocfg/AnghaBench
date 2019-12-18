#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int no_write; int own_data; void* data; void* read_pos; void* data_end; void* buf_end; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 void* px_alloc (int) ; 

MBuf *
mbuf_create(int len)
{
	MBuf	   *mbuf;

	if (!len)
		len = 8192;

	mbuf = px_alloc(sizeof *mbuf);
	mbuf->data = px_alloc(len);
	mbuf->buf_end = mbuf->data + len;
	mbuf->data_end = mbuf->data;
	mbuf->read_pos = mbuf->data;

	mbuf->no_write = false;
	mbuf->own_data = true;

	return mbuf;
}