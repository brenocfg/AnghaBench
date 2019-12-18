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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 int /*<<< orphan*/ * popen (char const*,char*) ; 
 int /*<<< orphan*/ * stdout ; 

bool
openQueryOutputFile(const char *fname, FILE **fout, bool *is_pipe)
{
	if (!fname || fname[0] == '\0')
	{
		*fout = stdout;
		*is_pipe = false;
	}
	else if (*fname == '|')
	{
		*fout = popen(fname + 1, "w");
		*is_pipe = true;
	}
	else
	{
		*fout = fopen(fname, "w");
		*is_pipe = false;
	}

	if (*fout == NULL)
	{
		pg_log_error("%s: %m", fname);
		return false;
	}

	return true;
}