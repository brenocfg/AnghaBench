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
typedef  int timelib_long ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 
 int sHOUR (int) ; 
 int sMIN (int) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static timelib_long timelib_parse_tz_cor(char **ptr)
{
	char *begin = *ptr, *end;
	timelib_long  tmp;

	while (isdigit(**ptr) || **ptr == ':') {
		++*ptr;
	}
	end = *ptr;
	switch (end - begin) {
		case 1: /* H */
		case 2: /* HH */
			return sHOUR(strtol(begin, NULL, 10));
			break;
		case 3: /* H:M */
		case 4: /* H:MM, HH:M, HHMM */
			if (begin[1] == ':') {
				tmp = sHOUR(strtol(begin, NULL, 10)) + sMIN(strtol(begin + 2, NULL, 10));
				return tmp;
			} else if (begin[2] == ':') {
				tmp = sHOUR(strtol(begin, NULL, 10)) + sMIN(strtol(begin + 3, NULL, 10));
				return tmp;
			} else {
				tmp = strtol(begin, NULL, 10);
				return sHOUR(tmp / 100) + sMIN(tmp % 100);
			}
		case 5: /* HH:MM */
			tmp = sHOUR(strtol(begin, NULL, 10)) + sMIN(strtol(begin + 3, NULL, 10));
			return tmp;
	}
	return 0;
}