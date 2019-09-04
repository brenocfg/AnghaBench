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
 scalar_t__ SUCCESS ; 
 char* get_help (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  pretty_print (char*) ; 

void phpdbg_do_help_cmd(char *type) { /* {{{ */
	char *help;

	if (!type) {
		pretty_print(get_help("overview!"));
		return;
	}

	help = get_help(type);

	if (!help || memcmp(help, "", sizeof("")) == SUCCESS) {
		pretty_print(get_help("overview!"));
		pretty_print(
			"\nrequested help page could not be found");
		return;
	}

	pretty_print(help);
}