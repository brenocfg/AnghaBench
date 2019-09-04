#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_compr_stream {TYPE_2__* runtime; TYPE_1__* ops; } ;
struct TYPE_6__ {unsigned int fragment_size; unsigned int fragments; } ;
struct snd_compr_params {TYPE_3__ buffer; } ;
struct TYPE_5__ {unsigned int fragment_size; unsigned int fragments; unsigned int buffer_size; void* buffer; } ;
struct TYPE_4__ {scalar_t__ copy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_compr_allocate_buffer(struct snd_compr_stream *stream,
		struct snd_compr_params *params)
{
	unsigned int buffer_size;
	void *buffer;

	buffer_size = params->buffer.fragment_size * params->buffer.fragments;
	if (stream->ops->copy) {
		buffer = NULL;
		/* if copy is defined the driver will be required to copy
		 * the data from core
		 */
	} else {
		buffer = kmalloc(buffer_size, GFP_KERNEL);
		if (!buffer)
			return -ENOMEM;
	}
	stream->runtime->fragment_size = params->buffer.fragment_size;
	stream->runtime->fragments = params->buffer.fragments;
	stream->runtime->buffer = buffer;
	stream->runtime->buffer_size = buffer_size;
	return 0;
}