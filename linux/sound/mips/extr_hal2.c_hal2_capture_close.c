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
struct snd_pcm_substream {int dummy; } ;
struct snd_hal2 {int /*<<< orphan*/  adc; } ;

/* Variables and functions */
 int /*<<< orphan*/  hal2_free_dmabuf (struct snd_hal2*,int /*<<< orphan*/ *) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	hal2_free_dmabuf(hal2, &hal2->adc);
	return 0;
}