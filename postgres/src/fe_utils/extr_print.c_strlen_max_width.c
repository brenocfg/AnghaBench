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
 int PQdsplen (char*,int) ; 
 int /*<<< orphan*/  PQmblen (char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
strlen_max_width(unsigned char *str, int *target_width, int encoding)
{
	unsigned char *start = str;
	unsigned char *end = str + strlen((char *) str);
	int			curr_width = 0;

	while (str < end)
	{
		int			char_width = PQdsplen((char *) str, encoding);

		/*
		 * If the display width of the new character causes the string to
		 * exceed its target width, skip it and return.  However, if this is
		 * the first character of the string (curr_width == 0), we have to
		 * accept it.
		 */
		if (*target_width < curr_width + char_width && curr_width != 0)
			break;

		curr_width += char_width;

		str += PQmblen((char *) str, encoding);
	}

	*target_width = curr_width;

	return str - start;
}