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
struct fjes_device_shared_info {int epnum; int* ep_status; } ;

/* Variables and functions */

int fjes_hw_epid_is_shared(struct fjes_device_shared_info *share,
			   int dest_epid)
{
	int value = false;

	if (dest_epid < share->epnum)
		value = share->ep_status[dest_epid];

	return value;
}