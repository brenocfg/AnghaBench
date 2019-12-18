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
struct cs4281_dma {int /*<<< orphan*/ * substream; } ;
struct TYPE_2__ {struct cs4281_dma* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int snd_cs4281_capture_close(struct snd_pcm_substream *substream)
{
	struct cs4281_dma *dma = substream->runtime->private_data;

	dma->substream = NULL;
	return 0;
}