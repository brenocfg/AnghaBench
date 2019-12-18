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
struct tomoyo_name_union {int /*<<< orphan*/ * filename; } ;
struct tomoyo_acl_param {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * tomoyo_get_dqword (char*) ; 
 int tomoyo_parse_name_union (struct tomoyo_acl_param*,struct tomoyo_name_union*) ; 

__attribute__((used)) static bool tomoyo_parse_name_union_quoted(struct tomoyo_acl_param *param,
					   struct tomoyo_name_union *ptr)
{
	char *filename = param->data;

	if (*filename == '@')
		return tomoyo_parse_name_union(param, ptr);
	ptr->filename = tomoyo_get_dqword(filename);
	return ptr->filename != NULL;
}