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
struct snd_pcm_runtime {unsigned int buffer_size; scalar_t__ dma_area; } ;
struct isight {unsigned int buffer_pointer; TYPE_1__* pcm; int /*<<< orphan*/  pcm_running; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isight_update_pointers (struct isight*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void isight_samples(struct isight *isight,
			   const __be16 *samples, unsigned int count)
{
	struct snd_pcm_runtime *runtime;
	unsigned int count1;

	if (!READ_ONCE(isight->pcm_running))
		return;

	runtime = isight->pcm->runtime;
	if (isight->buffer_pointer + count <= runtime->buffer_size) {
		memcpy(runtime->dma_area + isight->buffer_pointer * 4,
		       samples, count * 4);
	} else {
		count1 = runtime->buffer_size - isight->buffer_pointer;
		memcpy(runtime->dma_area + isight->buffer_pointer * 4,
		       samples, count1 * 4);
		samples += count1 * 2;
		memcpy(runtime->dma_area, samples, (count - count1) * 4);
	}

	isight_update_pointers(isight, count);
}