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
struct tomoyo_condition {scalar_t__ transit; } ;
struct tomoyo_acl_param {char* data; } ;

/* Variables and functions */
 char* strchr (char* const,char) ; 
 int /*<<< orphan*/  strcmp (char* const,char*) ; 
 scalar_t__ tomoyo_correct_path (char* const) ; 
 scalar_t__ tomoyo_get_domainname (struct tomoyo_acl_param*) ; 
 scalar_t__ tomoyo_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tomoyo_read_token (struct tomoyo_acl_param*) ; 

__attribute__((used)) static char *tomoyo_get_transit_preference(struct tomoyo_acl_param *param,
					   struct tomoyo_condition *e)
{
	char * const pos = param->data;
	bool flag;

	if (*pos == '<') {
		e->transit = tomoyo_get_domainname(param);
		goto done;
	}
	{
		char *cp = strchr(pos, ' ');

		if (cp)
			*cp = '\0';
		flag = tomoyo_correct_path(pos) || !strcmp(pos, "keep") ||
			!strcmp(pos, "initialize") || !strcmp(pos, "reset") ||
			!strcmp(pos, "child") || !strcmp(pos, "parent");
		if (cp)
			*cp = ' ';
	}
	if (!flag)
		return pos;
	e->transit = tomoyo_get_name(tomoyo_read_token(param));
done:
	if (e->transit)
		return param->data;
	/*
	 * Return a bad read-only condition string that will let
	 * tomoyo_get_condition() return NULL.
	 */
	return "/";
}