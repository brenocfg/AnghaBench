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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  redirect_to_stderr ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ui_helpline__vshow (char const*,int /*<<< orphan*/ ) ; 
 int use_browser ; 
 int vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int veprintf(int level, int var, const char *fmt, va_list args)
{
	int ret = 0;

	if (var >= level) {
		if (use_browser >= 1 && !redirect_to_stderr)
			ui_helpline__vshow(fmt, args);
		else
			ret = vfprintf(stderr, fmt, args);
	}

	return ret;
}