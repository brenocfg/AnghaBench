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
 int do_main () ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 
 int /*<<< orphan*/  print_opts () ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);
	print_opts();
	return do_main();
}