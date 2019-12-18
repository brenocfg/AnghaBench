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
struct tomoyo_name_union {int /*<<< orphan*/ * filename; int /*<<< orphan*/ * group; } ;
struct tomoyo_acl_param {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_PATH_GROUP ; 
 int /*<<< orphan*/  tomoyo_correct_word (char*) ; 
 int /*<<< orphan*/ * tomoyo_get_group (struct tomoyo_acl_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tomoyo_get_name (char*) ; 
 char* tomoyo_read_token (struct tomoyo_acl_param*) ; 

bool tomoyo_parse_name_union(struct tomoyo_acl_param *param,
			     struct tomoyo_name_union *ptr)
{
	char *filename;

	if (param->data[0] == '@') {
		param->data++;
		ptr->group = tomoyo_get_group(param, TOMOYO_PATH_GROUP);
		return ptr->group != NULL;
	}
	filename = tomoyo_read_token(param);
	if (!tomoyo_correct_word(filename))
		return false;
	ptr->filename = tomoyo_get_name(filename);
	return ptr->filename != NULL;
}