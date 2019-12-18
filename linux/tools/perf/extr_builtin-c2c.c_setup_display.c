#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_LCL ; 
 int /*<<< orphan*/  DISPLAY_RMT ; 
 int /*<<< orphan*/  DISPLAY_TOT ; 
 TYPE_1__ c2c ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int setup_display(const char *str)
{
	const char *display = str ?: "tot";

	if (!strcmp(display, "tot"))
		c2c.display = DISPLAY_TOT;
	else if (!strcmp(display, "rmt"))
		c2c.display = DISPLAY_RMT;
	else if (!strcmp(display, "lcl"))
		c2c.display = DISPLAY_LCL;
	else {
		pr_err("failed: unknown display type: %s\n", str);
		return -1;
	}

	return 0;
}