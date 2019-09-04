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
 int BUFSIZ ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gets (char*) ; 
 int /*<<< orphan*/  interactive ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

int confirm(const char *cmd, const char *file)
{
	char line[BUFSIZ];

	if (!interactive)
		return (1);
	printf("%s %s? ", cmd, file);
	(void) fflush(stdout);
	(void) gets(line);
	return (*line != 'n' && *line != 'N');
}