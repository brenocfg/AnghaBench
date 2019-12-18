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
struct dstr {char* array; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_ensure_capacity (struct dstr*,scalar_t__) ; 
 scalar_t__ dstr_is_empty (struct dstr*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strstr (char*,char const*) ; 

void dstr_replace(struct dstr *str, const char *find, const char *replace)
{
	size_t find_len, replace_len;
	char *temp;

	if (dstr_is_empty(str))
		return;

	if (!replace)
		replace = "";

	find_len = strlen(find);
	replace_len = strlen(replace);
	temp = str->array;

	if (replace_len < find_len) {
		unsigned long count = 0;

		while ((temp = strstr(temp, find)) != NULL) {
			char *end = temp + find_len;
			size_t end_len = strlen(end);

			if (end_len) {
				memmove(temp + replace_len, end, end_len + 1);
				if (replace_len)
					memcpy(temp, replace, replace_len);
			} else {
				strcpy(temp, replace);
			}

			temp += replace_len;
			++count;
		}

		if (count)
			str->len += (replace_len - find_len) * count;

	} else if (replace_len > find_len) {
		unsigned long count = 0;

		while ((temp = strstr(temp, find)) != NULL) {
			temp += find_len;
			++count;
		}

		if (!count)
			return;

		str->len += (replace_len - find_len) * count;
		dstr_ensure_capacity(str, str->len + 1);
		temp = str->array;

		while ((temp = strstr(temp, find)) != NULL) {
			char *end = temp + find_len;
			size_t end_len = strlen(end);

			if (end_len) {
				memmove(temp + replace_len, end, end_len + 1);
				memcpy(temp, replace, replace_len);
			} else {
				strcpy(temp, replace);
			}

			temp += replace_len;
		}

	} else {
		while ((temp = strstr(temp, find)) != NULL) {
			memcpy(temp, replace, replace_len);
			temp += replace_len;
		}
	}
}