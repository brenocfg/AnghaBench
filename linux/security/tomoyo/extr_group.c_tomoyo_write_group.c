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
typedef  scalar_t__ u8 ;
struct tomoyo_path_group {int /*<<< orphan*/  member_name; int /*<<< orphan*/  head; } ;
struct tomoyo_number_group {int /*<<< orphan*/  head; int /*<<< orphan*/  number; } ;
struct tomoyo_group {int /*<<< orphan*/  member_list; } ;
struct tomoyo_address_group {int /*<<< orphan*/  head; int /*<<< orphan*/  address; } ;
struct tomoyo_acl_param {char* data; int /*<<< orphan*/ * list; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ const TOMOYO_NUMBER_GROUP ; 
 scalar_t__ const TOMOYO_PATH_GROUP ; 
 struct tomoyo_group* tomoyo_get_group (struct tomoyo_acl_param*,scalar_t__ const) ; 
 int /*<<< orphan*/  tomoyo_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_parse_ipaddr_union (struct tomoyo_acl_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_parse_number_union (struct tomoyo_acl_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_put_group (struct tomoyo_group*) ; 
 int /*<<< orphan*/  tomoyo_put_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_read_token (struct tomoyo_acl_param*) ; 
 int /*<<< orphan*/  tomoyo_same_address_group ; 
 int /*<<< orphan*/  tomoyo_same_number_group ; 
 int /*<<< orphan*/  tomoyo_same_path_group ; 
 int tomoyo_update_policy (int /*<<< orphan*/ *,int,struct tomoyo_acl_param*,int /*<<< orphan*/ ) ; 

int tomoyo_write_group(struct tomoyo_acl_param *param, const u8 type)
{
	struct tomoyo_group *group = tomoyo_get_group(param, type);
	int error = -EINVAL;

	if (!group)
		return -ENOMEM;
	param->list = &group->member_list;
	if (type == TOMOYO_PATH_GROUP) {
		struct tomoyo_path_group e = { };

		e.member_name = tomoyo_get_name(tomoyo_read_token(param));
		if (!e.member_name) {
			error = -ENOMEM;
			goto out;
		}
		error = tomoyo_update_policy(&e.head, sizeof(e), param,
					  tomoyo_same_path_group);
		tomoyo_put_name(e.member_name);
	} else if (type == TOMOYO_NUMBER_GROUP) {
		struct tomoyo_number_group e = { };

		if (param->data[0] == '@' ||
		    !tomoyo_parse_number_union(param, &e.number))
			goto out;
		error = tomoyo_update_policy(&e.head, sizeof(e), param,
					  tomoyo_same_number_group);
		/*
		 * tomoyo_put_number_union() is not needed because
		 * param->data[0] != '@'.
		 */
	} else {
		struct tomoyo_address_group e = { };

		if (param->data[0] == '@' ||
		    !tomoyo_parse_ipaddr_union(param, &e.address))
			goto out;
		error = tomoyo_update_policy(&e.head, sizeof(e), param,
					     tomoyo_same_address_group);
	}
out:
	tomoyo_put_group(group);
	return error;
}