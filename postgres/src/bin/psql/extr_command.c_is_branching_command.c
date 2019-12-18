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
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static bool
is_branching_command(const char *cmd)
{
	return (strcmp(cmd, "if") == 0 ||
			strcmp(cmd, "elif") == 0 ||
			strcmp(cmd, "else") == 0 ||
			strcmp(cmd, "endif") == 0);
}