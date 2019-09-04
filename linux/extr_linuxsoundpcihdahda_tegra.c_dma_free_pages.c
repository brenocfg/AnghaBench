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

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 

__attribute__((used)) static void dma_free_pages(struct hdac_bus *bus, struct snd_dma_buffer *buf)
{
	snd_dma_free_pages(buf);
}