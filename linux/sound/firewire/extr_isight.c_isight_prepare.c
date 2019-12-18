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
struct isight {int /*<<< orphan*/  mutex; scalar_t__ period_counter; scalar_t__ buffer_pointer; } ;

/* Variables and functions */
 int isight_start_streaming (struct isight*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isight_prepare(struct snd_pcm_substream *substream)
{
	struct isight *isight = substream->private_data;
	int err;

	isight->buffer_pointer = 0;
	isight->period_counter = 0;

	mutex_lock(&isight->mutex);
	err = isight_start_streaming(isight);
	mutex_unlock(&isight->mutex);

	return err;
}