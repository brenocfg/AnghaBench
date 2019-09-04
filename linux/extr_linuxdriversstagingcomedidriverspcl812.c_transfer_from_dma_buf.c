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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,unsigned short*,int) ; 
 int /*<<< orphan*/  pcl812_ai_next_chan (struct comedi_device*,struct comedi_subdevice*) ; 

__attribute__((used)) static void transfer_from_dma_buf(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  unsigned short *ptr,
				  unsigned int bufptr, unsigned int len)
{
	unsigned int i;
	unsigned short val;

	for (i = len; i; i--) {
		val = ptr[bufptr++];
		comedi_buf_write_samples(s, &val, 1);

		if (!pcl812_ai_next_chan(dev, s))
			break;
	}
}