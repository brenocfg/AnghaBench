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
struct perf_hpp_list {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int output_field_add (struct perf_hpp_list*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 int /*<<< orphan*/  ui__error (char*,char*) ; 

__attribute__((used)) static int setup_output_list(struct perf_hpp_list *list, char *str)
{
	char *tmp, *tok;
	int ret = 0;

	for (tok = strtok_r(str, ", ", &tmp);
			tok; tok = strtok_r(NULL, ", ", &tmp)) {
		ret = output_field_add(list, tok);
		if (ret == -EINVAL) {
			ui__error("Invalid --fields key: `%s'", tok);
			break;
		} else if (ret == -ESRCH) {
			ui__error("Unknown --fields key: `%s'", tok);
			break;
		}
	}

	return ret;
}