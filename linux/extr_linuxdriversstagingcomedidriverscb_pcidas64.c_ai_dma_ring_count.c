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
struct pcidas64_board {scalar_t__ layout; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_4020 ; 
 unsigned int MAX_AI_DMA_RING_COUNT ; 
 unsigned int MIN_AI_DMA_RING_COUNT ; 

__attribute__((used)) static inline unsigned int ai_dma_ring_count(const struct pcidas64_board *board)
{
	if (board->layout == LAYOUT_4020)
		return MAX_AI_DMA_RING_COUNT;

	return MIN_AI_DMA_RING_COUNT;
}