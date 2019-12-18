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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct idma_ctrl* private_data; } ;
struct idma_ctrl {unsigned long start; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (struct snd_pcm_runtime*,unsigned long) ; 
 int /*<<< orphan*/  idma_getpos (unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static snd_pcm_uframes_t
	idma_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct idma_ctrl *prtd = runtime->private_data;
	dma_addr_t src;
	unsigned long res;

	spin_lock(&prtd->lock);

	idma_getpos(&src);
	res = src - prtd->start;

	spin_unlock(&prtd->lock);

	return bytes_to_frames(substream->runtime, res);
}