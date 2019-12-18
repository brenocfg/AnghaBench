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
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int parse_ip_val_buffer(char *in_buf, int *offset,
				char *out_buf, int out_len)
{
	char *x;
	char *start;

	/*
	 * in_buf has sequence of characters that are separated by
	 * the character ';'. The last sequence does not have the
	 * terminating ";" character.
	 */
	start = in_buf + *offset;

	x = strchr(start, ';');
	if (x)
		*x = 0;
	else
		x = start + strlen(start);

	if (strlen(start) != 0) {
		int i = 0;
		/*
		 * Get rid of leading spaces.
		 */
		while (start[i] == ' ')
			i++;

		if ((x - start) <= out_len) {
			strcpy(out_buf, (start + i));
			*offset += (x - start) + 1;
			return 1;
		}
	}
	return 0;
}