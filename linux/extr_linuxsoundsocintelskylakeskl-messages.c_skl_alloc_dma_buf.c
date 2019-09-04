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
struct snd_dma_buffer {int dummy; } ;
struct hdac_bus {TYPE_1__* io_ops; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int (* dma_alloc_pages ) (struct hdac_bus*,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 struct hdac_bus* dev_get_drvdata (struct device*) ; 
 int stub1 (struct hdac_bus*,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 

__attribute__((used)) static int skl_alloc_dma_buf(struct device *dev,
		struct snd_dma_buffer *dmab, size_t size)
{
	struct hdac_bus *bus = dev_get_drvdata(dev);

	if (!bus)
		return -ENODEV;

	return  bus->io_ops->dma_alloc_pages(bus, SNDRV_DMA_TYPE_DEV, size, dmab);
}