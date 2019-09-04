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
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exe_cp (char*,char*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prerequisites(void)
{
	int fd;
	const char *script = "#!/bin/sh\nexit $*\n";

	/* Create ephemeral copies of files */
	exe_cp("execveat", "execveat.ephemeral");
	exe_cp("execveat", "execveat.path.ephemeral");
	exe_cp("script", "script.ephemeral");
	mkdir("subdir.ephemeral", 0755);

	fd = open("subdir.ephemeral/script", O_RDWR|O_CREAT|O_TRUNC, 0755);
	write(fd, script, strlen(script));
	close(fd);
}