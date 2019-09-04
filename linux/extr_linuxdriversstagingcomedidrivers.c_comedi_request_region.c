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
struct comedi_device {unsigned long iobase; unsigned long iolen; } ;

/* Variables and functions */
 int __comedi_request_region (struct comedi_device*,unsigned long,unsigned long) ; 

int comedi_request_region(struct comedi_device *dev,
			  unsigned long start, unsigned long len)
{
	int ret;

	ret = __comedi_request_region(dev, start, len);
	if (ret == 0) {
		dev->iobase = start;
		dev->iolen = len;
	}

	return ret;
}