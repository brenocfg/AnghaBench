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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct idma_ctrl {int /*<<< orphan*/  start; int /*<<< orphan*/  pos; } ;
struct TYPE_2__ {struct idma_ctrl* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPAM_DMA_STOP ; 
 int /*<<< orphan*/  idma_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idma_enqueue (struct snd_pcm_substream*) ; 

__attribute__((used)) static int idma_prepare(struct snd_pcm_substream *substream)
{
	struct idma_ctrl *prtd = substream->runtime->private_data;

	prtd->pos = prtd->start;

	/* flush the DMA channel */
	idma_control(LPAM_DMA_STOP);
	idma_enqueue(substream);

	return 0;
}