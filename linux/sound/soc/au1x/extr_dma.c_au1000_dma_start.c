#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct audio_stream {int period_size; int /*<<< orphan*/  dma; TYPE_2__* buffer; } ;
struct TYPE_4__ {TYPE_1__* next; int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_dma_done0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_dma_done1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma_buffers (int /*<<< orphan*/ ) ; 
 scalar_t__ get_dma_active_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_addr0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_addr1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_count1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1000_dma_start(struct audio_stream *stream)
{
	if (!stream->buffer)
		return;

	init_dma(stream->dma);
	if (get_dma_active_buffer(stream->dma) == 0) {
		clear_dma_done0(stream->dma);
		set_dma_addr0(stream->dma, stream->buffer->start);
		set_dma_count0(stream->dma, stream->period_size >> 1);
		set_dma_addr1(stream->dma, stream->buffer->next->start);
		set_dma_count1(stream->dma, stream->period_size >> 1);
	} else {
		clear_dma_done1(stream->dma);
		set_dma_addr1(stream->dma, stream->buffer->start);
		set_dma_count1(stream->dma, stream->period_size >> 1);
		set_dma_addr0(stream->dma, stream->buffer->next->start);
		set_dma_count0(stream->dma, stream->period_size >> 1);
	}
	enable_dma_buffers(stream->dma);
	start_dma(stream->dma);
}