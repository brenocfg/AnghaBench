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
struct vdev_info {int nvqs; TYPE_1__* fds; } ;
struct TYPE_2__ {int revents; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int POLLIN ; 
 int /*<<< orphan*/  poll (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,unsigned long long*,int) ; 

__attribute__((used)) static void wait_for_interrupt(struct vdev_info *dev)
{
	int i;
	unsigned long long val;
	poll(dev->fds, dev->nvqs, -1);
	for (i = 0; i < dev->nvqs; ++i)
		if (dev->fds[i].revents & POLLIN) {
			read(dev->fds[i].fd, &val, sizeof val);
		}
}