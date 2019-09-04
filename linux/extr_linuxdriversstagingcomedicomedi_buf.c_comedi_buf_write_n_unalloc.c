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
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_async {unsigned int buf_read_count; unsigned int prealloc_bufsz; unsigned int buf_write_alloc_count; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int comedi_buf_write_n_unalloc(struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	unsigned int free_end = async->buf_read_count + async->prealloc_bufsz;

	return free_end - async->buf_write_alloc_count;
}