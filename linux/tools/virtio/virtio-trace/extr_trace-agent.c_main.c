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
struct agent_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  agent_info_free (struct agent_info*) ; 
 struct agent_info* agent_info_new () ; 
 int /*<<< orphan*/  agent_main_loop (struct agent_info*) ; 
 int /*<<< orphan*/  parse_args (int,char**,struct agent_info*) ; 

int main(int argc, char *argv[])
{
	struct agent_info *s = NULL;

	s = agent_info_new();
	parse_args(argc, argv, s);

	agent_main_loop(s);

	agent_info_free(s);

	return 0;
}