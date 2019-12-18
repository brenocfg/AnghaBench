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
 char* bmalloc (size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

char **strlist_split(const char *str, char split_ch, bool include_empty)
{
	const char *cur_str = str;
	const char *next_str;
	char *out = NULL;
	size_t count = 0;
	size_t total_size = 0;

	if (str) {
		char **table;
		char *offset;
		size_t cur_idx = 0;
		size_t cur_pos = 0;

		next_str = strchr(str, split_ch);

		while (next_str) {
			size_t size = next_str - cur_str;

			if (size || include_empty) {
				++count;
				total_size += size + 1;
			}

			cur_str = next_str + 1;
			next_str = strchr(cur_str, split_ch);
		}

		if (*cur_str || include_empty) {
			++count;
			total_size += strlen(cur_str) + 1;
		}

		/* ------------------ */

		cur_pos = (count + 1) * sizeof(char *);
		total_size += cur_pos;
		out = bmalloc(total_size);
		offset = out + cur_pos;
		table = (char **)out;

		/* ------------------ */

		next_str = strchr(str, split_ch);
		cur_str = str;

		while (next_str) {
			size_t size = next_str - cur_str;

			if (size || include_empty) {
				table[cur_idx++] = offset;
				strncpy(offset, cur_str, size);
				offset[size] = 0;
				offset += size + 1;
			}

			cur_str = next_str + 1;
			next_str = strchr(cur_str, split_ch);
		}

		if (*cur_str || include_empty) {
			table[cur_idx++] = offset;
			strcpy(offset, cur_str);
		}

		table[cur_idx] = NULL;
	}

	return (char **)out;
}