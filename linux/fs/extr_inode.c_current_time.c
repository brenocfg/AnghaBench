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
struct timespec64 {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 
 struct timespec64 timestamp_truncate (struct timespec64,struct inode*) ; 
 scalar_t__ unlikely (int) ; 

struct timespec64 current_time(struct inode *inode)
{
	struct timespec64 now;

	ktime_get_coarse_real_ts64(&now);

	if (unlikely(!inode->i_sb)) {
		WARN(1, "current_time() called with uninitialized super_block in the inode");
		return now;
	}

	return timestamp_truncate(now, inode);
}