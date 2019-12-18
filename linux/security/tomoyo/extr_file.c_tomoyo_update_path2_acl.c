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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct tomoyo_path2_acl {int /*<<< orphan*/  name2; int /*<<< orphan*/  name1; TYPE_1__ head; int /*<<< orphan*/  const perm; } ;
struct tomoyo_acl_param {int dummy; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TOMOYO_TYPE_PATH2_ACL ; 
 int /*<<< orphan*/  tomoyo_merge_path2_acl ; 
 int /*<<< orphan*/  tomoyo_parse_name_union (struct tomoyo_acl_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_put_name_union (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_same_path2_acl ; 
 int tomoyo_update_domain (TYPE_1__*,int,struct tomoyo_acl_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tomoyo_update_path2_acl(const u8 perm,
				   struct tomoyo_acl_param *param)
{
	struct tomoyo_path2_acl e = {
		.head.type = TOMOYO_TYPE_PATH2_ACL,
		.perm = perm
	};
	int error;

	if (!tomoyo_parse_name_union(param, &e.name1) ||
	    !tomoyo_parse_name_union(param, &e.name2))
		error = -EINVAL;
	else
		error = tomoyo_update_domain(&e.head, sizeof(e), param,
					     tomoyo_same_path2_acl,
					     tomoyo_merge_path2_acl);
	tomoyo_put_name_union(&e.name1);
	tomoyo_put_name_union(&e.name2);
	return error;
}