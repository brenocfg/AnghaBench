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
struct azx {int dummy; } ;

/* Variables and functions */
 struct azx* bus_to_azx (struct hdac_bus*) ; 
 int /*<<< orphan*/  mark_pages_wc (struct azx*,struct snd_dma_buffer*,int) ; 
 int snd_dma_alloc_pages (int,int /*<<< orphan*/ ,size_t,struct snd_dma_buffer*) ; 

__attribute__((used)) static int dma_alloc_pages(struct hdac_bus *bus,
			   int type,
			   size_t size,
			   struct snd_dma_buffer *buf)
{
	struct azx *chip = bus_to_azx(bus);
	int err;

	err = snd_dma_alloc_pages(type,
				  bus->dev,
				  size, buf);
	if (err < 0)
		return err;
	mark_pages_wc(chip, buf, true);
	return 0;
}