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
typedef  int /*<<< orphan*/  timelib_sll ;

/* Variables and functions */
 int /*<<< orphan*/  TIMELIB_UNSET ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strtoll (char*,int /*<<< orphan*/ *,int) ; 
 char* timelib_calloc (int,int) ; 
 int /*<<< orphan*/  timelib_free (char*) ; 

__attribute__((used)) static timelib_sll timelib_get_nr_ex(char **ptr, int max_length, int *scanned_length)
{
	char *begin, *end, *str;
	timelib_sll tmp_nr = TIMELIB_UNSET;
	int len = 0;

	while ((**ptr < '0') || (**ptr > '9')) {
		if (**ptr == '\0') {
			return TIMELIB_UNSET;
		}
		++*ptr;
	}
	begin = *ptr;
	while ((**ptr >= '0') && (**ptr <= '9') && len < max_length) {
		++*ptr;
		++len;
	}
	end = *ptr;
	if (scanned_length) {
		*scanned_length = end - begin;
	}
	str = timelib_calloc(1, end - begin + 1);
	memcpy(str, begin, end - begin);
	tmp_nr = strtoll(str, NULL, 10);
	timelib_free(str);
	return tmp_nr;
}