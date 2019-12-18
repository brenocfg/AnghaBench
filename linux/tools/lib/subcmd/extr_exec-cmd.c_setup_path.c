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
 int /*<<< orphan*/  add_path (char**,char*) ; 
 char* argv0_path ; 
 int /*<<< orphan*/  astrcat (char**,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_argv_exec_path () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

void setup_path(void)
{
	const char *old_path = getenv("PATH");
	char *new_path = NULL;
	char *tmp = get_argv_exec_path();

	add_path(&new_path, tmp);
	add_path(&new_path, argv0_path);
	free(tmp);

	if (old_path)
		astrcat(&new_path, old_path);
	else
		astrcat(&new_path, "/usr/local/bin:/usr/bin:/bin");

	setenv("PATH", new_path, 1);

	free(new_path);
}