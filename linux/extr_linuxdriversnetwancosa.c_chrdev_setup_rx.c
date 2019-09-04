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
struct channel_data {int rxsize; char* rxdata; } ;

/* Variables and functions */

__attribute__((used)) static char *chrdev_setup_rx(struct channel_data *chan, int size)
{
	/* Expect size <= COSA_MTU */
	chan->rxsize = size;
	return chan->rxdata;
}