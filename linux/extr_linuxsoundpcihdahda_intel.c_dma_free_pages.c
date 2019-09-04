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
struct hdac_bus {int dummy; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 struct azx* bus_to_azx (struct hdac_bus*) ; 
 int /*<<< orphan*/  mark_pages_wc (struct azx*,struct snd_dma_buffer*,int) ; 
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 

__attribute__((used)) static void dma_free_pages(struct hdac_bus *bus, struct snd_dma_buffer *buf)
{
	struct azx *chip = bus_to_azx(bus);

	mark_pages_wc(chip, buf, false);
	snd_dma_free_pages(buf);
}