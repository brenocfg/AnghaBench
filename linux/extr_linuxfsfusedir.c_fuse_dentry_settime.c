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
union fuse_dentry {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  u64 ;
struct dentry {scalar_t__ d_fsdata; } ;

/* Variables and functions */

__attribute__((used)) static inline void fuse_dentry_settime(struct dentry *entry, u64 time)
{
	((union fuse_dentry *) entry->d_fsdata)->time = time;
}