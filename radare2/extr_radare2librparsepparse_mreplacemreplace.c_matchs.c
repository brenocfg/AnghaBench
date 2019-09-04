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
typedef  int /*<<< orphan*/  RRegex ;

/* Variables and functions */
 int R_REGEX_EXTENDED ; 
 int R_REGEX_NOSUB ; 
 scalar_t__ r_regex_comp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ r_regex_exec (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_regex_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_regex_new (char*,char*) ; 

int matchs(const char *string, char *pattern) {
	int status = 0;
	RRegex *re = r_regex_new (pattern, "");
	if (!re) {
		return status;
	}
	if (r_regex_comp (re, pattern, R_REGEX_EXTENDED|R_REGEX_NOSUB) == 0) {
		status = r_regex_exec (re, string, (size_t) 0, NULL, 0)? 1: 0;
	}
	r_regex_free (re);
	return status;
}