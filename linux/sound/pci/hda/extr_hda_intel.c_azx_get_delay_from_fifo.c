#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct TYPE_3__ {struct snd_pcm_substream* substream; } ;
struct azx_dev {TYPE_1__ core; } ;
struct azx {int dummy; } ;
struct TYPE_4__ {int delay; } ;

/* Variables and functions */

__attribute__((used)) static int azx_get_delay_from_fifo(struct azx *chip, struct azx_dev *azx_dev,
				   unsigned int pos)
{
	struct snd_pcm_substream *substream = azx_dev->core.substream;

	/* just read back the calculated value in the above */
	return substream->runtime->delay;
}