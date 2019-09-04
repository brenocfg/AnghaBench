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
struct timespec64 {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_time_gran; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct timespec64 current_kernel_time64 () ; 
 struct timespec64 timespec64_trunc (struct timespec64,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct timespec64 current_time(struct inode *inode)
{
	struct timespec64 now = current_kernel_time64();

	if (unlikely(!inode->i_sb)) {
		WARN(1, "current_time() called with uninitialized super_block in the inode");
		return now;
	}

	return timespec64_trunc(now, inode->i_sb->s_time_gran);
}