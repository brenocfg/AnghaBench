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
struct cpdma_chan {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CPDMA_STATE_ACTIVE ; 
 int EINVAL ; 
 int __cpdma_chan_process (struct cpdma_chan*) ; 

int cpdma_chan_process(struct cpdma_chan *chan, int quota)
{
	int used = 0, ret = 0;

	if (chan->state != CPDMA_STATE_ACTIVE)
		return -EINVAL;

	while (used < quota) {
		ret = __cpdma_chan_process(chan);
		if (ret < 0)
			break;
		used++;
	}
	return used;
}