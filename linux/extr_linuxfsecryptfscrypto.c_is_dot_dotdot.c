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

__attribute__((used)) static bool is_dot_dotdot(const char *name, size_t name_size)
{
	if (name_size == 1 && name[0] == '.')
		return true;
	else if (name_size == 2 && name[0] == '.' && name[1] == '.')
		return true;

	return false;
}