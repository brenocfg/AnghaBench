#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int no_write; int own_data; int /*<<< orphan*/ * data; int /*<<< orphan*/ * read_pos; int /*<<< orphan*/ * data_end; int /*<<< orphan*/ * buf_end; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 TYPE_1__* px_alloc (int) ; 

MBuf *
mbuf_create_from_data(uint8 *data, int len)
{
	MBuf	   *mbuf;

	mbuf = px_alloc(sizeof *mbuf);
	mbuf->data = (uint8 *) data;
	mbuf->buf_end = mbuf->data + len;
	mbuf->data_end = mbuf->data + len;
	mbuf->read_pos = mbuf->data;

	mbuf->no_write = true;
	mbuf->own_data = false;

	return mbuf;
}