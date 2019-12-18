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
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *
find_end_token(char *str, char *fmt)
{
	/*
	 * str: here is28the day12the hour fmt: here is%dthe day%hthe hour
	 *
	 * we extract the 28, we read the percent sign and the type "d" then this
	 * functions gets called as find_end_token("28the day12the hour", "the
	 * day%hthehour")
	 *
	 * fmt points to "the day%hthehour", next_percent points to %hthehour and
	 * we have to find a match for everything between these positions ("the
	 * day"). We look for "the day" in str and know that the pattern we are
	 * about to scan ends where this string starts (right after the "28")
	 *
	 * At the end, *fmt is '\0' and *str isn't. end_position then is
	 * unchanged.
	 */
	char	   *end_position = NULL;
	char	   *next_percent,
			   *subst_location = NULL;
	int			scan_offset = 0;
	char		last_char;

	/* are we at the end? */
	if (!*fmt)
	{
		end_position = fmt;
		return end_position;
	}

	/* not at the end */
	while (fmt[scan_offset] == '%' && fmt[scan_offset + 1])
	{
		/*
		 * there is no delimiter, skip to the next delimiter if we're reading
		 * a number and then something that is not a number "9:15pm", we might
		 * be able to recover with the strtol end pointer. Go for the next
		 * percent sign
		 */
		scan_offset += 2;
	}
	next_percent = strchr(fmt + scan_offset, '%');
	if (next_percent)
	{
		/*
		 * we don't want to allocate extra memory, so we temporarily set the
		 * '%' sign to '\0' and call strstr However since we allow whitespace
		 * to float around everything, we have to shorten the pattern until we
		 * reach a non-whitespace character
		 */

		subst_location = next_percent;
		while (*(subst_location - 1) == ' ' && subst_location - 1 > fmt + scan_offset)
			subst_location--;
		last_char = *subst_location;
		*subst_location = '\0';

		/*
		 * the haystack is the str and the needle is the original fmt but it
		 * ends at the position where the next percent sign would be
		 */

		/*
		 * There is one special case. Imagine: str = " 2", fmt = "%d %...",
		 * since we want to allow blanks as "dynamic" padding we have to
		 * accept this. Now, we are called with a fmt of " %..." and look for
		 * " " in str. We find it at the first position and never read the
		 * 2...
		 */
		while (*str == ' ')
			str++;
		end_position = strstr(str, fmt + scan_offset);
		*subst_location = last_char;
	}
	else
	{
		/*
		 * there is no other percent sign. So everything up to the end has to
		 * match.
		 */
		end_position = str + strlen(str);
	}
	if (!end_position)
	{
		/*
		 * maybe we have the following case:
		 *
		 * str = "4:15am" fmt = "%M:%S %p"
		 *
		 * at this place we could have
		 *
		 * str = "15am" fmt = " %p"
		 *
		 * and have set fmt to " " because overwrote the % sign with a NULL
		 *
		 * In this case where we would have to match a space but can't find
		 * it, set end_position to the end of the string
		 */
		if ((fmt + scan_offset)[0] == ' ' && fmt + scan_offset + 1 == subst_location)
			end_position = str + strlen(str);
	}
	return end_position;
}