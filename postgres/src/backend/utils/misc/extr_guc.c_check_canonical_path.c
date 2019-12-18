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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  canonicalize_path (char*) ; 

__attribute__((used)) static bool
check_canonical_path(char **newval, void **extra, GucSource source)
{
	/*
	 * Since canonicalize_path never enlarges the string, we can just modify
	 * newval in-place.  But watch out for NULL, which is the default value
	 * for external_pid_file.
	 */
	if (*newval)
		canonicalize_path(*newval);
	return true;
}