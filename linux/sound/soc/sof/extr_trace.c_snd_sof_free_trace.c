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
struct snd_sof_dev {int /*<<< orphan*/  dmatp; int /*<<< orphan*/  dmatb; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sof_release_trace (struct snd_sof_dev*) ; 

void snd_sof_free_trace(struct snd_sof_dev *sdev)
{
	snd_sof_release_trace(sdev);

	snd_dma_free_pages(&sdev->dmatb);
	snd_dma_free_pages(&sdev->dmatp);
}