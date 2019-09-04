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
struct tomoyo_argv {int /*<<< orphan*/ * value; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_VALUE_TYPE_DECIMAL ; 
 int /*<<< orphan*/ * tomoyo_get_dqword (char*) ; 
 scalar_t__ tomoyo_parse_ulong (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static bool tomoyo_parse_argv(char *left, char *right,
			      struct tomoyo_argv *argv)
{
	if (tomoyo_parse_ulong(&argv->index, &left) !=
	    TOMOYO_VALUE_TYPE_DECIMAL || *left++ != ']' || *left)
		return false;
	argv->value = tomoyo_get_dqword(right);
	return argv->value != NULL;
}