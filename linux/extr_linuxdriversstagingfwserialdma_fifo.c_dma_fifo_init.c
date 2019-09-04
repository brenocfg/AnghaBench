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
struct dma_fifo {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dma_fifo*,int /*<<< orphan*/ ,int) ; 

void dma_fifo_init(struct dma_fifo *fifo)
{
	memset(fifo, 0, sizeof(*fifo));
	INIT_LIST_HEAD(&fifo->pending);
}