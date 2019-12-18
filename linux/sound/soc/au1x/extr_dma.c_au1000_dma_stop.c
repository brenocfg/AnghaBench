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
struct audio_stream {int /*<<< orphan*/  dma; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1000_dma_stop(struct audio_stream *stream)
{
	if (stream->buffer)
		disable_dma(stream->dma);
}