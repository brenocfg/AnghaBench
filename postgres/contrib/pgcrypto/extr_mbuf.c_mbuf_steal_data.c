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
struct TYPE_4__ {int no_write; int own_data; int /*<<< orphan*/ * buf_end; int /*<<< orphan*/ * read_pos; int /*<<< orphan*/ * data_end; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ MBuf ;

/* Variables and functions */
 int mbuf_size (TYPE_1__*) ; 

int
mbuf_steal_data(MBuf *mbuf, uint8 **data_p)
{
	int			len = mbuf_size(mbuf);

	mbuf->no_write = true;
	mbuf->own_data = false;

	*data_p = mbuf->data;

	mbuf->data = mbuf->data_end = mbuf->read_pos = mbuf->buf_end = NULL;

	return len;
}