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
struct pcidas64_private {int ao_dma_index; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 int AO_DMA_RING_COUNT ; 

__attribute__((used)) static inline unsigned int prev_ao_dma_index(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned int buffer_index;

	if (devpriv->ao_dma_index == 0)
		buffer_index = AO_DMA_RING_COUNT - 1;
	else
		buffer_index = devpriv->ao_dma_index - 1;
	return buffer_index;
}