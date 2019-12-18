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
 char* decode_str (char*) ; 
 int /*<<< orphan*/  strlist_free (char**) ; 
 char** strlist_split (char const*,char,int) ; 

extern void build_window_strings(const char *str, char **class, char **title,
				 char **exe)
{
	char **strlist;

	*class = NULL;
	*title = NULL;
	*exe = NULL;

	if (!str) {
		return;
	}

	strlist = strlist_split(str, ':', true);

	if (strlist && strlist[0] && strlist[1] && strlist[2]) {
		*title = decode_str(strlist[0]);
		*class = decode_str(strlist[1]);
		*exe = decode_str(strlist[2]);
	}

	strlist_free(strlist);
}