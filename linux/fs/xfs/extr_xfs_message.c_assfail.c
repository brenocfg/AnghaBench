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
struct TYPE_2__ {scalar_t__ bug_on_assert; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  xfs_emerg (int /*<<< orphan*/ *,char*,char*,char*,int) ; 
 TYPE_1__ xfs_globals ; 

void
assfail(char *expr, char *file, int line)
{
	xfs_emerg(NULL, "Assertion failed: %s, file: %s, line: %d",
		expr, file, line);
	if (xfs_globals.bug_on_assert)
		BUG();
	else
		WARN_ON(1);
}