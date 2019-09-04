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
struct kstat {int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_set_timestamps(struct dentry *upperdentry, struct kstat *stat)
{
	struct iattr attr = {
		.ia_valid =
		     ATTR_ATIME | ATTR_MTIME | ATTR_ATIME_SET | ATTR_MTIME_SET,
		.ia_atime = stat->atime,
		.ia_mtime = stat->mtime,
	};

	return notify_change(upperdentry, &attr, NULL);
}