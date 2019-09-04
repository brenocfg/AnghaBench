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
struct pcm_period {struct pcm_period* next; } ;
struct audio_stream {struct pcm_period* buffer; scalar_t__ periods; scalar_t__ period_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pcm_period*) ; 

__attribute__((used)) static void au1000_release_dma_link(struct audio_stream *stream)
{
	struct pcm_period *pointer;
	struct pcm_period *pointer_next;

	stream->period_size = 0;
	stream->periods = 0;
	pointer = stream->buffer;
	if (!pointer)
		return;
	do {
		pointer_next = pointer->next;
		kfree(pointer);
		pointer = pointer_next;
	} while (pointer != stream->buffer);
	stream->buffer = NULL;
}