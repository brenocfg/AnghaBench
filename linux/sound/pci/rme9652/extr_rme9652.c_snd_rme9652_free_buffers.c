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
struct snd_rme9652 {int /*<<< orphan*/  pci; int /*<<< orphan*/  playback_dma_buf; int /*<<< orphan*/  capture_dma_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hammerfall_free_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_rme9652_free_buffers(struct snd_rme9652 *rme9652)
{
	snd_hammerfall_free_buffer(&rme9652->capture_dma_buf, rme9652->pci);
	snd_hammerfall_free_buffer(&rme9652->playback_dma_buf, rme9652->pci);
}