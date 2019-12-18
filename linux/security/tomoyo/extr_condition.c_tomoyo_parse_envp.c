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
struct tomoyo_envp {struct tomoyo_path_info const* value; struct tomoyo_path_info const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tomoyo_correct_word (char*) ; 
 struct tomoyo_path_info* tomoyo_get_dqword (char*) ; 
 struct tomoyo_path_info* tomoyo_get_name (char*) ; 
 int /*<<< orphan*/  tomoyo_put_name (struct tomoyo_path_info const*) ; 

__attribute__((used)) static bool tomoyo_parse_envp(char *left, char *right,
			      struct tomoyo_envp *envp)
{
	const struct tomoyo_path_info *name;
	const struct tomoyo_path_info *value;
	char *cp = left + strlen(left) - 1;

	if (*cp-- != ']' || *cp != '"')
		goto out;
	*cp = '\0';
	if (!tomoyo_correct_word(left))
		goto out;
	name = tomoyo_get_name(left);
	if (!name)
		goto out;
	if (!strcmp(right, "NULL")) {
		value = NULL;
	} else {
		value = tomoyo_get_dqword(right);
		if (!value) {
			tomoyo_put_name(name);
			goto out;
		}
	}
	envp->name = name;
	envp->value = value;
	return true;
out:
	return false;
}