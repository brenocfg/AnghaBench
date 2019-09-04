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
struct comedi_async {scalar_t__ events; scalar_t__ munge_ptr; scalar_t__ munge_count; scalar_t__ munge_chan; scalar_t__ scan_progress; scalar_t__ scans_done; scalar_t__ cur_chan; scalar_t__ buf_read_ptr; scalar_t__ buf_write_ptr; scalar_t__ buf_read_count; scalar_t__ buf_read_alloc_count; scalar_t__ buf_write_count; scalar_t__ buf_write_alloc_count; } ;

/* Variables and functions */

void comedi_buf_reset(struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;

	async->buf_write_alloc_count = 0;
	async->buf_write_count = 0;
	async->buf_read_alloc_count = 0;
	async->buf_read_count = 0;

	async->buf_write_ptr = 0;
	async->buf_read_ptr = 0;

	async->cur_chan = 0;
	async->scans_done = 0;
	async->scan_progress = 0;
	async->munge_chan = 0;
	async->munge_count = 0;
	async->munge_ptr = 0;

	async->events = 0;
}