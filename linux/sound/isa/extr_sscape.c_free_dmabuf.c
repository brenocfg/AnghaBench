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
struct snd_dma_buffer {scalar_t__ area; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (struct snd_dma_buffer*) ; 

__attribute__((used)) static void free_dmabuf(struct snd_dma_buffer *buf)
{
	if (buf && buf->area)
		snd_dma_free_pages(buf);
}