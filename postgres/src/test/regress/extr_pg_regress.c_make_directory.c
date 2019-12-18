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
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char*) ; 
 scalar_t__ mkdir (char const*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_directory(const char *dir)
{
	if (mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO) < 0)
	{
		fprintf(stderr, _("%s: could not create directory \"%s\": %s\n"),
				progname, dir, strerror(errno));
		exit(2);
	}
}