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
 scalar_t__ astrcmpi_n (char const*,char const*,int /*<<< orphan*/ ) ; 
 char** internal_microsoft_exes ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool is_microsoft_internal_window_exe(const char *exe)
{
	if (!exe)
		return false;

	for (const char **vals = internal_microsoft_exes; *vals; vals++) {
		if (astrcmpi_n(exe, *vals, strlen(*vals)) == 0)
			return true;
	}

	return false;
}