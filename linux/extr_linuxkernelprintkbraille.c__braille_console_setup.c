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
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int _braille_console_setup(char **str, char **brl_options)
{
	if (!strncmp(*str, "brl,", 4)) {
		*brl_options = "";
		*str += 4;
	} else if (!strncmp(*str, "brl=", 4)) {
		*brl_options = *str + 4;
		*str = strchr(*brl_options, ',');
		if (!*str) {
			pr_err("need port name after brl=\n");
			return -EINVAL;
		}
		*((*str)++) = 0;
	}

	return 0;
}