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
struct ef4_rx_queue {int dummy; } ;
struct TYPE_2__ {int channel; } ;

/* Variables and functions */
 TYPE_1__* ef4_rx_queue_channel (struct ef4_rx_queue*) ; 

__attribute__((used)) static inline int ef4_rx_queue_index(struct ef4_rx_queue *rx_queue)
{
	return ef4_rx_queue_channel(rx_queue)->channel;
}