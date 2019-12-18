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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  print_help () ; 
 int /*<<< orphan*/  print_man_page (char const*) ; 

__attribute__((used)) static int cmd_help(int argc, const char **argv)
{
	if (argc > 1) {
		print_man_page(argv[1]); /* exits within execlp() */
		return EXIT_FAILURE;
	}

	print_help();
	return EXIT_SUCCESS;
}