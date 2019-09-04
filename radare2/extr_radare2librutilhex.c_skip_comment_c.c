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

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

const char *skip_comment_c(const char *code) {
	if (!strncmp (code, "/*", 2)) {
		char *end = strstr (code, "*/");
		if (end) {
			code = end + 2;
		} else {
			eprintf ("Missing closing comment\n");
		}
	} else if (!strncmp (code, "//", 2)) {
		char *end = strchr (code, '\n');
		if (end) {
			code = end + 2;
		}
	}
	return code;
}