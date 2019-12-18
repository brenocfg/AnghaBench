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
struct sprd_compr_stream {scalar_t__ copied_total; scalar_t__ received_total; struct sprd_compr_dma* dma; } ;
struct sprd_compr_dma {scalar_t__ trans_len; } ;
struct snd_compr_stream {struct snd_compr_runtime* runtime; } ;
struct snd_compr_runtime {struct sprd_compr_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_compr_fragment_elapsed (struct snd_compr_stream*) ; 

__attribute__((used)) static void sprd_platform_compr_dma_complete(void *data)
{
	struct snd_compr_stream *cstream = data;
	struct snd_compr_runtime *runtime = cstream->runtime;
	struct sprd_compr_stream *stream = runtime->private_data;
	struct sprd_compr_dma *dma = &stream->dma[1];

	/* Update data size copied to IRAM buffer */
	stream->copied_total += dma->trans_len;
	if (stream->copied_total > stream->received_total)
		stream->copied_total = stream->received_total;

	snd_compr_fragment_elapsed(cstream);
}