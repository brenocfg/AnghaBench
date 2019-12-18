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
struct dentry {int dummy; } ;
struct TYPE_2__ {struct dentry* debugfsdir; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fragmentation_threshold ; 
 int /*<<< orphan*/  ht40allow_map ; 
 int /*<<< orphan*/  long_retry_limit ; 
 int /*<<< orphan*/  rts_threshold ; 
 int /*<<< orphan*/  short_retry_limit ; 

void cfg80211_debugfs_rdev_add(struct cfg80211_registered_device *rdev)
{
	struct dentry *phyd = rdev->wiphy.debugfsdir;

	DEBUGFS_ADD(rts_threshold);
	DEBUGFS_ADD(fragmentation_threshold);
	DEBUGFS_ADD(short_retry_limit);
	DEBUGFS_ADD(long_retry_limit);
	DEBUGFS_ADD(ht40allow_map);
}