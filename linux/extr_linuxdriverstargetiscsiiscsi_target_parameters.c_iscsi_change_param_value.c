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
struct iscsi_param_list {int dummy; } ;
struct iscsi_param {int set_param; } ;

/* Variables and functions */
 struct iscsi_param* __iscsi_check_key (char*,int,struct iscsi_param_list*) ; 
 struct iscsi_param* iscsi_check_key (char*,int /*<<< orphan*/ ,int,struct iscsi_param_list*) ; 
 scalar_t__ iscsi_check_value (struct iscsi_param*,char*) ; 
 scalar_t__ iscsi_extract_key_value (char*,char**,char**) ; 
 scalar_t__ iscsi_update_param_value (struct iscsi_param*,char*) ; 

int iscsi_change_param_value(
	char *keyvalue,
	struct iscsi_param_list *param_list,
	int check_key)
{
	char *key = NULL, *value = NULL;
	struct iscsi_param *param;
	int sender = 0;

	if (iscsi_extract_key_value(keyvalue, &key, &value) < 0)
		return -1;

	if (!check_key) {
		param = __iscsi_check_key(keyvalue, sender, param_list);
		if (!param)
			return -1;
	} else {
		param = iscsi_check_key(keyvalue, 0, sender, param_list);
		if (!param)
			return -1;

		param->set_param = 1;
		if (iscsi_check_value(param, value) < 0) {
			param->set_param = 0;
			return -1;
		}
		param->set_param = 0;
	}

	if (iscsi_update_param_value(param, value) < 0)
		return -1;

	return 0;
}