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
struct pcidas64_private {scalar_t__ plx9080_iobase; } ;
struct comedi_device {struct pcidas64_private* private; } ;

/* Variables and functions */
 unsigned int PLX_DMADPR_CHAINEND ; 
 scalar_t__ PLX_REG_DMADPR0 ; 
 int /*<<< orphan*/  dma_start_sync (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_first_dma_descriptor (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void restart_ao_dma(struct comedi_device *dev)
{
	struct pcidas64_private *devpriv = dev->private;
	unsigned int dma_desc_bits;

	dma_desc_bits = readl(devpriv->plx9080_iobase + PLX_REG_DMADPR0);
	dma_desc_bits &= ~PLX_DMADPR_CHAINEND;
	load_first_dma_descriptor(dev, 0, dma_desc_bits);

	dma_start_sync(dev, 0);
}