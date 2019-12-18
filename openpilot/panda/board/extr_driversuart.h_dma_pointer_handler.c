#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_3__ {unsigned int rx_fifo_size; unsigned int r_ptr_rx; unsigned int w_ptr_rx; } ;
typedef  TYPE_1__ uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_CRITICAL () ; 
 int /*<<< orphan*/  EXIT_CRITICAL () ; 
 unsigned int prev_w_index ; 

void dma_pointer_handler(uart_ring *q, uint32_t dma_ndtr) {
  ENTER_CRITICAL();
  uint32_t w_index = (q->rx_fifo_size - dma_ndtr);
  
  // Check for new data
  if (w_index != prev_w_index){
    // Check for overflow
    if (
      ((prev_w_index < q->r_ptr_rx) && (q->r_ptr_rx <= w_index)) ||                               // No rollover
      ((w_index < prev_w_index) && ((q->r_ptr_rx <= w_index) || (prev_w_index < q->r_ptr_rx)))    // Rollover
    ){   
      // We lost data. Set the new read pointer to the oldest byte still available
      q->r_ptr_rx = (w_index + 1U) % q->rx_fifo_size;
    }

    // Set write pointer
    q->w_ptr_rx = w_index;
  }

  prev_w_index = w_index;
  EXIT_CRITICAL();
}