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
struct tomoyo_path_info {int dummy; } ;
struct tomoyo_acl_param {char* data; } ;

/* Variables and functions */
 scalar_t__ tomoyo_correct_domain (char*) ; 
 struct tomoyo_path_info const* tomoyo_get_name (char*) ; 

const struct tomoyo_path_info *tomoyo_get_domainname
(struct tomoyo_acl_param *param)
{
	char *start = param->data;
	char *pos = start;

	while (*pos) {
		if (*pos++ != ' ' || *pos++ == '/')
			continue;
		pos -= 2;
		*pos++ = '\0';
		break;
	}
	param->data = pos;
	if (tomoyo_correct_domain(start))
		return tomoyo_get_name(start);
	return NULL;
}