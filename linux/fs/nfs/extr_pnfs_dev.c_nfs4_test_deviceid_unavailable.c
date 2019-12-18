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
struct nfs4_deviceid_node {int /*<<< orphan*/  flags; int /*<<< orphan*/  timestamp_unavailable; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DEVICEID_UNAVAILABLE ; 
 unsigned long PNFS_DEVICE_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_in_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

bool
nfs4_test_deviceid_unavailable(struct nfs4_deviceid_node *node)
{
	if (test_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags)) {
		unsigned long start, end;

		end = jiffies;
		start = end - PNFS_DEVICE_RETRY_TIMEOUT;
		if (time_in_range(node->timestamp_unavailable, start, end))
			return true;
		clear_bit(NFS_DEVICEID_UNAVAILABLE, &node->flags);
		smp_mb__after_atomic();
	}
	return false;
}