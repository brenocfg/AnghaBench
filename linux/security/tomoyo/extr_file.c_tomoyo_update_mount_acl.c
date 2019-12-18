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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct tomoyo_mount_acl {int /*<<< orphan*/  flags; int /*<<< orphan*/  fs_type; int /*<<< orphan*/  dir_name; int /*<<< orphan*/  dev_name; TYPE_1__ head; } ;
struct tomoyo_acl_param {int dummy; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TOMOYO_TYPE_MOUNT_ACL ; 
 int /*<<< orphan*/  tomoyo_parse_name_union (struct tomoyo_acl_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_parse_number_union (struct tomoyo_acl_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_put_name_union (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_put_number_union (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_same_mount_acl ; 
 int tomoyo_update_domain (TYPE_1__*,int,struct tomoyo_acl_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tomoyo_update_mount_acl(struct tomoyo_acl_param *param)
{
	struct tomoyo_mount_acl e = { .head.type = TOMOYO_TYPE_MOUNT_ACL };
	int error;

	if (!tomoyo_parse_name_union(param, &e.dev_name) ||
	    !tomoyo_parse_name_union(param, &e.dir_name) ||
	    !tomoyo_parse_name_union(param, &e.fs_type) ||
	    !tomoyo_parse_number_union(param, &e.flags))
		error = -EINVAL;
	else
		error = tomoyo_update_domain(&e.head, sizeof(e), param,
					     tomoyo_same_mount_acl, NULL);
	tomoyo_put_name_union(&e.dev_name);
	tomoyo_put_name_union(&e.dir_name);
	tomoyo_put_name_union(&e.fs_type);
	tomoyo_put_number_union(&e.flags);
	return error;
}