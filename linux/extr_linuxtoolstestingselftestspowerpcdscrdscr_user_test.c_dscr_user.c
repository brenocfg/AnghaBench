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
 int COUNT ; 
 scalar_t__ check_dscr (char*) ; 
 int /*<<< orphan*/  set_dscr (int) ; 
 int /*<<< orphan*/  set_dscr_usr (int) ; 

int dscr_user(void)
{
	int i;

	check_dscr("");

	for (i = 0; i < COUNT; i++) {
		set_dscr(i);
		if (check_dscr("kernel"))
			return 1;
	}

	for (i = 0; i < COUNT; i++) {
		set_dscr_usr(i);
		if (check_dscr("user"))
			return 1;
	}
	return 0;
}