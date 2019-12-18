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
 int cmd_select (int /*<<< orphan*/ ,int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmds ; 
 int /*<<< orphan*/  do_help ; 

int do_btf(int argc, char **argv)
{
	return cmd_select(cmds, argc, argv, do_help);
}