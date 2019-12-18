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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IXUSR ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int is_executable(const char *name)
{
	struct stat st;

	if (stat(name, &st) || /* stat, not lstat */
	    !S_ISREG(st.st_mode))
		return 0;

	return st.st_mode & S_IXUSR;
}