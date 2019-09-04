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
typedef  double timelib_sll ;

/* Variables and functions */
 double TIMELIB_UNSET ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 double pow (int,int) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 
 char* timelib_calloc (int,int) ; 
 int /*<<< orphan*/  timelib_free (char*) ; 

__attribute__((used)) static timelib_sll timelib_get_frac_nr(char **ptr, int max_length)
{
	char *begin, *end, *str;
	double tmp_nr = TIMELIB_UNSET;
	int len = 0;

	while ((**ptr != '.') && (**ptr != ':') && ((**ptr < '0') || (**ptr > '9'))) {
		if (**ptr == '\0') {
			return TIMELIB_UNSET;
		}
		++*ptr;
	}
	begin = *ptr;
	while (((**ptr == '.') || (**ptr == ':') || ((**ptr >= '0') && (**ptr <= '9'))) && len < max_length) {
		++*ptr;
		++len;
	}
	end = *ptr;
	str = timelib_calloc(1, end - begin);
	memcpy(str, begin + 1, end - begin - 1);
	tmp_nr = strtod(str, NULL) * pow(10, 7 - (end - begin));
	timelib_free(str);
	return tmp_nr;
}