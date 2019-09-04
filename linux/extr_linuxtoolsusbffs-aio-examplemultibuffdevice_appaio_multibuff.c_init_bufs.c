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
struct io_buffer {unsigned int cnt; unsigned int len; void** iocb; void** buf; scalar_t__ requested; } ;

/* Variables and functions */
 void* malloc (int) ; 

void init_bufs(struct io_buffer *iobuf, unsigned n, unsigned len)
{
	unsigned i;
	iobuf->buf = malloc(n*sizeof(*iobuf->buf));
	iobuf->iocb = malloc(n*sizeof(*iobuf->iocb));
	iobuf->cnt = n;
	iobuf->len = len;
	iobuf->requested = 0;
	for (i = 0; i < n; ++i) {
		iobuf->buf[i] = malloc(len*sizeof(**iobuf->buf));
		iobuf->iocb[i] = malloc(sizeof(**iobuf->iocb));
	}
	iobuf->cnt = n;
}