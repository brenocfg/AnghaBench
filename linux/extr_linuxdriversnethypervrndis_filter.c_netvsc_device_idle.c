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
struct netvsc_device {int num_chn; struct netvsc_channel* chan_table; } ;
struct TYPE_2__ {scalar_t__ first; scalar_t__ next; } ;
struct netvsc_channel {int /*<<< orphan*/  queue_sends; TYPE_1__ mrc; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool netvsc_device_idle(const struct netvsc_device *nvdev)
{
	int i;

	for (i = 0; i < nvdev->num_chn; i++) {
		const struct netvsc_channel *nvchan = &nvdev->chan_table[i];

		if (nvchan->mrc.first != nvchan->mrc.next)
			return false;

		if (atomic_read(&nvchan->queue_sends) > 0)
			return false;
	}

	return true;
}