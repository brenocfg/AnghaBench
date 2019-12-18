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
typedef  int /*<<< orphan*/  cmd_parms ;

/* Variables and functions */
 char const* real_value_hnd (int /*<<< orphan*/ *,void*,char const*,char*,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static const char *real_flag_hnd(cmd_parms *cmd, void *dummy, const char *arg1, const char *arg2, int status)
{
	char bool_val[2];

	if (!strcasecmp(arg2, "On") || (arg2[0] == '1' && arg2[1] == '\0')) {
		bool_val[0] = '1';
	} else {
		bool_val[0] = '0';
	}
	bool_val[1] = 0;

	return real_value_hnd(cmd, dummy, arg1, bool_val, status);
}