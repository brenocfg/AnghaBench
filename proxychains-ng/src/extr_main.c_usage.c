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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int usage(char **argv) {
	printf("\nUsage:\t%s -q -f config_file program_name [arguments]\n"
	       "\t-q makes proxychains quiet - this overrides the config setting\n"
	       "\t-f allows one to manually specify a configfile to use\n"
	       "\tfor example : proxychains telnet somehost.com\n" "More help in README file\n\n", argv[0]);
	return EXIT_FAILURE;
}