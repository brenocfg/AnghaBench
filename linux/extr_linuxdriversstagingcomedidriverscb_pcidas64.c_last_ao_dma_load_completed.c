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
struct pcidas64_private {unsigned int* ao_buffer_bus_addr; scalar_t__ plx9080_iobase; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 unsigned short PLX_DMACSR_DONE ; 
 scalar_t__ PLX_REG_DMACSR0 ; 
 scalar_t__ PLX_REG_DMAPADR0 ; 
 unsigned int prev_ao_dma_index (struct comedi_device*) ; 
 unsigned short readb (scalar_t__) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int last_ao_dma_load_completed(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned int buffer_index;
	unsigned int transfer_address;
	unsigned short dma_status;

	buffer_index = prev_ao_dma_index(dev);
	dma_status = readb(devpriv->plx9080_iobase + PLX_REG_DMACSR0);
	if ((dma_status & PLX_DMACSR_DONE) == 0)
		return 0;

	transfer_address =
		readl(devpriv->plx9080_iobase + PLX_REG_DMAPADR0);
	if (transfer_address != devpriv->ao_buffer_bus_addr[buffer_index])
		return 0;

	return 1;
}