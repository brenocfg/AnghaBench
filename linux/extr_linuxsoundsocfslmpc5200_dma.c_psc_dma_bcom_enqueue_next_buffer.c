#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct psc_dma_stream {int period_bytes; int period_next; TYPE_1__* runtime; int /*<<< orphan*/  bcom_task; } ;
struct bcom_bd {int status; scalar_t__* data; } ;
struct TYPE_2__ {int periods; scalar_t__ dma_addr; } ;

/* Variables and functions */
 struct bcom_bd* bcom_prepare_next_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_submit_next_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psc_dma_bcom_enqueue_next_buffer(struct psc_dma_stream *s)
{
	struct bcom_bd *bd;

	/* Prepare and enqueue the next buffer descriptor */
	bd = bcom_prepare_next_buffer(s->bcom_task);
	bd->status = s->period_bytes;
	bd->data[0] = s->runtime->dma_addr + (s->period_next * s->period_bytes);
	bcom_submit_next_buffer(s->bcom_task, NULL);

	/* Update for next period */
	s->period_next = (s->period_next + 1) % s->runtime->periods;
}