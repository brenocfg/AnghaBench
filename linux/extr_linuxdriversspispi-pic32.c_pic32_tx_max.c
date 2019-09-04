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
typedef  int u32 ;
struct pic32_spi {int tx_end; int tx; int fifo_n_elm; int rx_end; int rx; } ;

/* Variables and functions */
 int min3 (int,int,int) ; 
 int pic32_tx_fifo_level (struct pic32_spi*) ; 

__attribute__((used)) static u32 pic32_tx_max(struct pic32_spi *pic32s, int n_bytes)
{
	u32 tx_left, tx_room, rxtx_gap;

	tx_left = (pic32s->tx_end - pic32s->tx) / n_bytes;
	tx_room = pic32s->fifo_n_elm - pic32_tx_fifo_level(pic32s);

	/*
	 * Another concern is about the tx/rx mismatch, we
	 * though to use (pic32s->fifo_n_byte - rxfl - txfl) as
	 * one maximum value for tx, but it doesn't cover the
	 * data which is out of tx/rx fifo and inside the
	 * shift registers. So a ctrl from sw point of
	 * view is taken.
	 */
	rxtx_gap = ((pic32s->rx_end - pic32s->rx) -
		    (pic32s->tx_end - pic32s->tx)) / n_bytes;
	return min3(tx_left, tx_room, (u32)(pic32s->fifo_n_elm - rxtx_gap));
}