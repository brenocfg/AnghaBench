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
struct action_fifo {scalar_t__ tail; scalar_t__ head; } ;

/* Variables and functions */

__attribute__((used)) static void action_fifo_init(struct action_fifo *fifo)
{
	fifo->head = 0;
	fifo->tail = 0;
}