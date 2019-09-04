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
struct comedi_async {unsigned int buf_read_count; unsigned int buf_read_ptr; unsigned int prealloc_bufsz; } ;

/* Variables and functions */
 unsigned int comedi_buf_read_n_allocated (struct comedi_async*) ; 
 int /*<<< orphan*/  smp_mb () ; 

unsigned int comedi_buf_read_free(struct comedi_subdevice *s,
				  unsigned int nbytes)
{
	struct comedi_async *async = s->async;
	unsigned int allocated;

	/*
	 * ensure data has been read out of buffer before
	 * the async read count is incremented
	 */
	smp_mb();

	allocated = comedi_buf_read_n_allocated(async);
	if (nbytes > allocated)
		nbytes = allocated;

	async->buf_read_count += nbytes;
	async->buf_read_ptr += nbytes;
	async->buf_read_ptr %= async->prealloc_bufsz;
	return nbytes;
}