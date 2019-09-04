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
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int read_block(char *buf, int buf_size, FILE *fin)
{
	char *curr = buf, *const buf_end = buf + buf_size;

	while (buf_end - curr > 1 && fgets(curr, buf_end - curr, fin)) {
		if (*curr == '\n') /* empty line */
			return curr - buf;
		curr += strlen(curr);
	}

	return -1; /* EOF or no space left in buf. */
}