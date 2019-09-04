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
struct snd_dma_buffer {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int snd_dma_alloc_pages (int,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 

__attribute__((used)) static int hdac_ext_dma_alloc_pages(struct hdac_bus *bus, int type,
			   size_t size, struct snd_dma_buffer *buf)
{
	return snd_dma_alloc_pages(type, bus->dev, size, buf);
}