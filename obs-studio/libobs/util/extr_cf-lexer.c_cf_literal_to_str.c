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
 char* bzalloc (size_t) ; 
 int /*<<< orphan*/  cf_convert_from_escape_literal (char**,char const**) ; 
 size_t strlen (char const*) ; 

char *cf_literal_to_str(const char *literal, size_t count)
{
	const char *temp_src;
	char *str, *temp_dst;

	if (!count)
		count = strlen(literal);

	if (count < 2)
		return NULL;
	if (literal[0] != literal[count - 1])
		return NULL;
	if (literal[0] != '\"' && literal[0] != '\'')
		return NULL;

	/* strip leading and trailing quote characters */
	str = bzalloc(--count);
	temp_src = literal + 1;
	temp_dst = str;

	while (*temp_src && --count > 0) {
		if (*temp_src == '\\') {
			temp_src++;
			cf_convert_from_escape_literal(&temp_dst, &temp_src);
		} else {
			*(temp_dst++) = *(temp_src++);
		}
	}

	*temp_dst = 0;
	return str;
}