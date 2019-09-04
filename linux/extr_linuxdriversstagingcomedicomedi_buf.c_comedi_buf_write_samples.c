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
struct comedi_subdevice {TYPE_2__* async; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/  events; } ;
struct TYPE_3__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_BLOCK ; 
 int /*<<< orphan*/  COMEDI_CB_OVERFLOW ; 
 int /*<<< orphan*/  comedi_buf_memcpy_to (struct comedi_subdevice*,void const*,unsigned int) ; 
 unsigned int comedi_buf_write_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_write_free (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_buf_write_n_unalloc (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_inc_scan_progress (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_samples_to_bytes (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

unsigned int comedi_buf_write_samples(struct comedi_subdevice *s,
				      const void *data, unsigned int nsamples)
{
	unsigned int max_samples;
	unsigned int nbytes;

	/*
	 * Make sure there is enough room in the buffer for all the samples.
	 * If not, clamp the nsamples to the number that will fit, flag the
	 * buffer overrun and add the samples that fit.
	 */
	max_samples = comedi_bytes_to_samples(s, comedi_buf_write_n_unalloc(s));
	if (nsamples > max_samples) {
		dev_warn(s->device->class_dev, "buffer overrun\n");
		s->async->events |= COMEDI_CB_OVERFLOW;
		nsamples = max_samples;
	}

	if (nsamples == 0)
		return 0;

	nbytes = comedi_buf_write_alloc(s,
					comedi_samples_to_bytes(s, nsamples));
	comedi_buf_memcpy_to(s, data, nbytes);
	comedi_buf_write_free(s, nbytes);
	comedi_inc_scan_progress(s, nbytes);
	s->async->events |= COMEDI_CB_BLOCK;

	return nbytes;
}