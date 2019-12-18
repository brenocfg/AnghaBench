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
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  tomoyo_alphabet_char (char const) ; 
 int /*<<< orphan*/  tomoyo_byte_range (char const*) ; 

__attribute__((used)) static bool tomoyo_file_matches_pattern2(const char *filename,
					 const char *filename_end,
					 const char *pattern,
					 const char *pattern_end)
{
	while (filename < filename_end && pattern < pattern_end) {
		char c;
		int i;
		int j;

		if (*pattern != '\\') {
			if (*filename++ != *pattern++)
				return false;
			continue;
		}
		c = *filename;
		pattern++;
		switch (*pattern) {
		case '?':
			if (c == '/') {
				return false;
			} else if (c == '\\') {
				if (filename[1] == '\\')
					filename++;
				else if (tomoyo_byte_range(filename + 1))
					filename += 3;
				else
					return false;
			}
			break;
		case '\\':
			if (c != '\\')
				return false;
			if (*++filename != '\\')
				return false;
			break;
		case '+':
			if (!isdigit(c))
				return false;
			break;
		case 'x':
			if (!isxdigit(c))
				return false;
			break;
		case 'a':
			if (!tomoyo_alphabet_char(c))
				return false;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
			if (c == '\\' && tomoyo_byte_range(filename + 1)
			    && strncmp(filename + 1, pattern, 3) == 0) {
				filename += 3;
				pattern += 2;
				break;
			}
			return false; /* Not matched. */
		case '*':
		case '@':
			for (i = 0; i <= filename_end - filename; i++) {
				if (tomoyo_file_matches_pattern2(
						    filename + i, filename_end,
						    pattern + 1, pattern_end))
					return true;
				c = filename[i];
				if (c == '.' && *pattern == '@')
					break;
				if (c != '\\')
					continue;
				if (filename[i + 1] == '\\')
					i++;
				else if (tomoyo_byte_range(filename + i + 1))
					i += 3;
				else
					break; /* Bad pattern. */
			}
			return false; /* Not matched. */
		default:
			j = 0;
			c = *pattern;
			if (c == '$') {
				while (isdigit(filename[j]))
					j++;
			} else if (c == 'X') {
				while (isxdigit(filename[j]))
					j++;
			} else if (c == 'A') {
				while (tomoyo_alphabet_char(filename[j]))
					j++;
			}
			for (i = 1; i <= j; i++) {
				if (tomoyo_file_matches_pattern2(
						    filename + i, filename_end,
						    pattern + 1, pattern_end))
					return true;
			}
			return false; /* Not matched or bad pattern. */
		}
		filename++;
		pattern++;
	}
	while (*pattern == '\\' &&
	       (*(pattern + 1) == '*' || *(pattern + 1) == '@'))
		pattern += 2;
	return filename == filename_end && pattern == pattern_end;
}