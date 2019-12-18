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
 int EXEC_ARGS_MAX ; 
 scalar_t__ ISBLANK (char) ; 

__attribute__((used)) static int parseargs(char *line, char **argv)
{
	int count = 0;

	argv[count++] = line;

	while (*line) { // NOLINT
		if (ISBLANK(*line)) {
			*line++ = '\0';

			if (!*line) // NOLINT
				return count;

			argv[count++] = line;
			if (count == EXEC_ARGS_MAX)
				return -1;
		}

		++line;
	}

	return count;
}