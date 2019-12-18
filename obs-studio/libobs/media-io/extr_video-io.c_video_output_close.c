#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t cache_size; } ;
struct TYPE_9__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_8__ {int /*<<< orphan*/  input_mutex; int /*<<< orphan*/  data_mutex; int /*<<< orphan*/  update_semaphore; int /*<<< orphan*/ * cache; TYPE_1__ info; TYPE_5__ inputs; } ;
typedef  TYPE_2__ video_t ;
struct video_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 
 int /*<<< orphan*/  da_free (TYPE_5__) ; 
 int /*<<< orphan*/  os_sem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_frame_free (struct video_frame*) ; 
 int /*<<< orphan*/  video_input_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_output_stop (TYPE_2__*) ; 

void video_output_close(video_t *video)
{
	if (!video)
		return;

	video_output_stop(video);

	for (size_t i = 0; i < video->inputs.num; i++)
		video_input_free(&video->inputs.array[i]);
	da_free(video->inputs);

	for (size_t i = 0; i < video->info.cache_size; i++)
		video_frame_free((struct video_frame *)&video->cache[i]);

	os_sem_destroy(video->update_semaphore);
	pthread_mutex_destroy(&video->data_mutex);
	pthread_mutex_destroy(&video->input_mutex);
	bfree(video);
}