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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_dentry_time (struct dentry const*) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int time_before64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_dentry_delete(const struct dentry *dentry)
{
	return time_before64(fuse_dentry_time(dentry), get_jiffies_64());
}