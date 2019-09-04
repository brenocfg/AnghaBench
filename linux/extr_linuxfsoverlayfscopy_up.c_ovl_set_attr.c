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
struct kstat {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_set_timestamps (struct dentry*,struct kstat*) ; 

int ovl_set_attr(struct dentry *upperdentry, struct kstat *stat)
{
	int err = 0;

	if (!S_ISLNK(stat->mode)) {
		struct iattr attr = {
			.ia_valid = ATTR_MODE,
			.ia_mode = stat->mode,
		};
		err = notify_change(upperdentry, &attr, NULL);
	}
	if (!err) {
		struct iattr attr = {
			.ia_valid = ATTR_UID | ATTR_GID,
			.ia_uid = stat->uid,
			.ia_gid = stat->gid,
		};
		err = notify_change(upperdentry, &attr, NULL);
	}
	if (!err)
		ovl_set_timestamps(upperdentry, stat);

	return err;
}