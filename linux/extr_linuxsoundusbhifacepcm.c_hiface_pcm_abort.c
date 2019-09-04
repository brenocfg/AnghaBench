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
struct pcm_runtime {int panic; int /*<<< orphan*/  stream_mutex; } ;
struct hiface_chip {struct pcm_runtime* pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  hiface_pcm_stream_stop (struct pcm_runtime*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void hiface_pcm_abort(struct hiface_chip *chip)
{
	struct pcm_runtime *rt = chip->pcm;

	if (rt) {
		rt->panic = true;

		mutex_lock(&rt->stream_mutex);
		hiface_pcm_stream_stop(rt);
		mutex_unlock(&rt->stream_mutex);
	}
}