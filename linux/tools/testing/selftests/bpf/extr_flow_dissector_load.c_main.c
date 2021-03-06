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
 scalar_t__ cfg_attach ; 
 int /*<<< orphan*/  detach_program () ; 
 int /*<<< orphan*/  load_and_attach_program () ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);
	if (cfg_attach)
		load_and_attach_program();
	else
		detach_program();
	return 0;
}