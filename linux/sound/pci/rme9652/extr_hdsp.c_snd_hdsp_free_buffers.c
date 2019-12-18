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
struct hdsp {int /*<<< orphan*/  pci; int /*<<< orphan*/  playback_dma_buf; int /*<<< orphan*/  capture_dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hammerfall_free_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hdsp_free_buffers(struct hdsp *hdsp)
{
	snd_hammerfall_free_buffer(&hdsp->capture_dma_buf, hdsp->pci);
	snd_hammerfall_free_buffer(&hdsp->playback_dma_buf, hdsp->pci);
}