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
struct snd_pcm_substream {struct isight* private_data; } ;
struct isight {int /*<<< orphan*/  mutex; int /*<<< orphan*/  pcm_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isight_stop_streaming (struct isight*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_vmalloc_buffer (struct snd_pcm_substream*) ; 

__attribute__((used)) static int isight_hw_free(struct snd_pcm_substream *substream)
{
	struct isight *isight = substream->private_data;

	WRITE_ONCE(isight->pcm_active, false);

	mutex_lock(&isight->mutex);
	isight_stop_streaming(isight);
	mutex_unlock(&isight->mutex);

	return snd_pcm_lib_free_vmalloc_buffer(substream);
}