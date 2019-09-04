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
struct ef4_rx_queue {int dummy; } ;
struct ef4_rx_buffer {int dummy; } ;
struct ef4_channel {int dummy; } ;

/* Variables and functions */
 struct ef4_rx_queue* ef4_channel_get_rx_queue (struct ef4_channel*) ; 
 int /*<<< orphan*/  ef4_recycle_rx_page (struct ef4_channel*,struct ef4_rx_buffer*) ; 
 struct ef4_rx_buffer* ef4_rx_buf_next (struct ef4_rx_queue*,struct ef4_rx_buffer*) ; 

__attribute__((used)) static void ef4_recycle_rx_pages(struct ef4_channel *channel,
				 struct ef4_rx_buffer *rx_buf,
				 unsigned int n_frags)
{
	struct ef4_rx_queue *rx_queue = ef4_channel_get_rx_queue(channel);

	do {
		ef4_recycle_rx_page(channel, rx_buf);
		rx_buf = ef4_rx_buf_next(rx_queue, rx_buf);
	} while (--n_frags);
}