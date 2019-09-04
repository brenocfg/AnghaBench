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
struct comedi_device {unsigned long iobase; } ;

/* Variables and functions */
 int PCMUIO_ASIC_IOSIZE ; 

__attribute__((used)) static inline unsigned long pcmuio_asic_iobase(struct comedi_device *dev,
					       int asic)
{
	return dev->iobase + (asic * PCMUIO_ASIC_IOSIZE);
}