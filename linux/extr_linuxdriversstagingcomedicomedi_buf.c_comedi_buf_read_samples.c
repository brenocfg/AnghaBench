#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_1__* async; } ;
struct TYPE_2__ {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMEDI_CB_BLOCK ; 
 int /*<<< orphan*/  comedi_buf_memcpy_from (struct comedi_subdevice*,void*,unsigned int) ; 
 unsigned int comedi_buf_read_alloc (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_buf_read_free (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_buf_read_n_available (struct comedi_subdevice*) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_inc_scan_progress (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_samples_to_bytes (struct comedi_subdevice*,unsigned int) ; 

unsigned int comedi_buf_read_samples(struct comedi_subdevice *s,
				     void *data, unsigned int nsamples)
{
	unsigned int max_samples;
	unsigned int nbytes;

	/* clamp nsamples to the number of full samples available */
	max_samples = comedi_bytes_to_samples(s,
					      comedi_buf_read_n_available(s));
	if (nsamples > max_samples)
		nsamples = max_samples;

	if (nsamples == 0)
		return 0;

	nbytes = comedi_buf_read_alloc(s,
				       comedi_samples_to_bytes(s, nsamples));
	comedi_buf_memcpy_from(s, data, nbytes);
	comedi_buf_read_free(s, nbytes);
	comedi_inc_scan_progress(s, nbytes);
	s->async->events |= COMEDI_CB_BLOCK;

	return nbytes;
}